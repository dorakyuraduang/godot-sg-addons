#include "group_obj.h"
#include "utils.h"
#include "static_obj.h"
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;
GroupObj::GroupObj()
{
}
GroupObj::~GroupObj()
{
}
void GroupObj::_ready()
{
  for (int i = 0; i < objects.size(); i++)
  {
    Object::cast_to<Node2D>(objects[i])->set_z_index(0);
    add_child(Object::cast_to<Node2D>(objects[i]));
  }
}
void GroupObj::load(Ref<CPtr> &ptr)
{
  int pos = ptr->get_pos();
  ptr->pos_add(68);
  String grp_path = ptr->get_str();
  load_all_static_obj(grp_path);
  ptr->set_pos(pos);
  int file_size = ptr->read_u32();
  ptr->pos_add(4);
  int x = ptr->read_s32();
  int y = ptr->read_s32();
  fixed_bound.position.x = ptr->read_s32();
  fixed_bound.position.y = ptr->read_s32();
  fixed_bound.size.x = ptr->read_s32();
  fixed_bound.size.y = ptr->read_s32();
  render_center.x = ptr->read_s32();
  render_center.y = ptr->read_s32();
  set_modulate(Utils::hex_to_color(ptr->read_u32()));
  set_rotation(ptr->read_float());
  float scale_x = ptr->read_float();
  float scale_y = ptr->read_float();
  set_scale(Vector2(scale_x, scale_y));
  set_effect(ptr->read_u32());
  int render_lv = ptr->read_u32();
  render_prority=ptr->read_u32();
  ptr->set_pos(pos + file_size);
  set_position(Vector2(x, y) + (-render_center - (fixed_bound.size+fixed_bound.position)) * get_scale());

}
void GroupObj::set_effect(int value)
{
  int a = value >> 8;
  int b = value >> 9;
  bool flip_h = bool(a & 0x1);
  bool flip_v = bool(b & 0x1);
  int color_mode = value & 0xf;
  for (int i = 0; i < objects.size(); i++)
  {
    StaticObj *obj = Object::cast_to<StaticObj>(objects[i]);
    if (flip_h)
    {
      obj->set_flip_h(!obj->is_flipped_h());
    }
    if (flip_v)
    {
      obj->set_flip_v(!obj->is_flipped_v());
    }
  }
}
void GroupObj::load_all_static_obj(String path)
{
  PackedByteArray data = FileAccess::get_file_as_bytes(path);
  Ref<CPtr> ptr;
  ptr.instantiate();
  ptr->set_data(data);
  int static_obj_count = ptr->read_u32();
  for (int i = 0; i < static_obj_count; i++)
  {
    StaticObj *static_obj = memnew(StaticObj);
    static_obj->initialize_class();
    static_obj->load(ptr);
    objects.append(static_obj);
  }
  objects.sort_custom(callable_mp(this, &GroupObj::objects_sort));
}
bool GroupObj::objects_sort(Variant a, Variant b)
{
  return Object::cast_to<MapRenerobj>(a)->render_prority < cast_to<MapRenerobj>(b)->render_prority;
}
void GroupObj::_bind_methods()
{
}