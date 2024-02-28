#include "static_obj.h"
#include "t_image.h"
#include <math.h>
#include "spline.h"
#include "spline_mgr.h"
#include "key_frame.h"
#include <godot_cpp/classes/engine.hpp>
// #include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/method_tweener.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/math.hpp>
using namespace godot;
StaticObj::StaticObj()
{
  ani_time = 0.0;
  frame = 0;
  ani_frame = 0;
}
StaticObj::~StaticObj()
{
}
void StaticObj::load(Ref<CPtr> &ptr)
{
  set_centered(false);
  set_z_as_relative(false);
  int pos = ptr->get_pos();
  file_size = ptr->read_u32();
  int version = ptr->read_u32();
  int x = ptr->read_s32();
  int y = ptr->read_s32();
  set_position(Vector2(x, y));
  fixed_bound.position.x = ptr->read_s32();
  fixed_bound.position.y = ptr->read_s32();
  fixed_bound.size.x = ptr->read_s32();
  fixed_bound.size.y = ptr->read_s32();
  render_center.x = ptr->read_s32();
  render_center.y = ptr->read_s32();

  image_center.x = int(fixed_bound.size.x) >> 1;
  image_center.y = int(fixed_bound.size.y) >> 1;
  set_color(ptr->read_u32());
  set_rotation(ptr->read_float());
  float scale_x = ptr->read_float();
  float scale_y = ptr->read_float();
  set_scale(Vector2(scale_x, scale_y));
  set_effect(ptr->read_u32());
  int render_lv = ptr->read_u32();
  render_prority = ptr->read_u32();
  set_offset((render_center - image_center));
  if (version == 5)
  {
    ptr->set_pos(pos + 0x14c);
    bool is_ani = ptr->read_bool();
    ptr->set_pos(pos + 0x48);
    id_image = ResourceLoader::get_singleton()->load(ptr->get_str());
    if (is_ani)
    {
      ptr->set_pos(pos + 0x164);
      load_ani_data(ptr);
    }
  }
  else if (version == 6)
  {
    ptr->set_pos(pos + 0x170);
    bool is_ani = ptr->read_bool();
    ptr->set_pos(pos + 0x6c);
    id_image = ResourceLoader::get_singleton()->load(ptr->get_str());
    if (is_ani)
    {
      ptr->set_pos(pos + 0x188);
      load_ani_data(ptr);
    }
  }
  ptr->set_pos(pos + file_size);
  set_frame(0);
}
void StaticObj::set_color(int value)
{
  float b = ((value >> 0) & 0xff) / 255.0;
  float g = ((value >> 8) & 0xff) / 255.0;
  float r = ((value >> 16) & 0xff) / 255.0;
  float a = ((value >> 24) & 0xff) / 255.0;
  set_modulate(Color(r, g, b, a));
}
void StaticObj::set_effect(int value)
{
  int a = value >> 8;
  int b = value >> 9;
  set_flip_h(bool(a & 0x1));
  set_flip_v(bool(b & 0x1));
  int color_mode = value & 0xf;
}

void StaticObj::_physics_process(double delta)
{
  if (id_image.is_null())
  {
    return;
  }
    ani_time += delta;
    Ref<TImage> image = Resource::cast_to<TImage>(id_image->images[frame]);
    while (ani_time > image->next_frame_time)
    {
      ani_time -= image->next_frame_time;
      if (frame >= id_image->frames - 1)
      {
        set_frame(0);
      }
      else
      {
        set_frame(++frame);
      }
    }
  }
  void StaticObj::_ready()
  {
  if (id_image.is_null())
  {
    return;
  }
  if (id_image->frames <= 1)
  {
    set_physics_process(false);
  }
  if (!ani_data.is_null() && ani_data->attach_to_path)
  {
    ani_start();
  }
}
void StaticObj::set_frame(int f)
{
  frame = f;
  if (!id_image.is_null())
  {
    set_texture(ImageTexture::create_from_image(id_image->images[frame]));
    set_offset((-render_center - image_center) + Resource::cast_to<TImage>(id_image->images[frame])->ani_pos);
  }
}
void StaticObj::load_ani_data(Ref<CPtr> &ptr)
{
  ani_data.instantiate();
  ani_data->load(ptr);
}
void StaticObj::ani_start()
{
  ani_frame = 0;
  ani_play();
}
void StaticObj::ani_play()
{

  Ref<KeyFrame> cur_key_frame = ani_data->key_frames[ani_frame];
  Ref<KeyFrame> next_key_frame = ani_data->key_frames[ani_frame + 1];
  double time = next_key_frame->time - cur_key_frame->time;
  Ref<Tween> tween = Object::cast_to<SceneTree>(Engine::get_singleton()->get_main_loop())->create_tween();
  tween->set_parallel(true);
  if (ani_data->spline_path > 0)
  {
    Ref<Spline> spline = SplineMgr::get_singleton()->get_spline(ani_data->spline_path);
    Vector2 cur_pos = spline->get_pos(cur_key_frame->scalar);
    Vector2 next_pos = spline->get_pos(next_key_frame->scalar);
    tween->tween_method(callable_mp(Object::cast_to<Node2D>(this), &StaticObj::set_position), cur_pos, next_pos, time)->set_ease(Tween::EASE_OUT_IN);
  }

  tween->tween_method(callable_mp(Object::cast_to<Node2D>(this), &StaticObj::set_scale), cur_key_frame->scale, next_key_frame->scale, time);
  tween->tween_method(callable_mp(Object::cast_to<CanvasItem>(this), &StaticObj::set_modulate), cur_key_frame->color, next_key_frame->color, time);
  // UtilityFunctions::print(cur_key_frame->rotation);
  tween->tween_method(callable_mp(Object::cast_to<Node2D>(this), &StaticObj::set_rotation_degrees), cur_key_frame->rotation, next_key_frame->rotation, time);
  tween->connect("finished", callable_mp(this, &StaticObj::ani_frame_end));
}
void StaticObj::ani_end()
{
  // UtilityFunctions::print(ani_data->repeat);
  if (ani_data->repeat)
  {
    ani_start();
  }
}
void StaticObj::ani_frame_end()
{
  if (ani_frame >= ani_data->key_frames.size() - 2)
  {
    ani_end();
  }
  else
  {
    ani_frame += 1;
    ani_play();
  }
}
Ref<AniData> StaticObj::get_ani_data()
{
  return ani_data;
}
void StaticObj::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("get_ani_data"), &StaticObj::get_ani_data);
  ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ani_data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_ani_data");
}