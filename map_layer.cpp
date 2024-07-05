#include "map_layer.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include "map_renderableobj.h"
#include "group_obj.h"
using namespace godot;

MapLayer::MapLayer()
{
  parallax_layer = memnew(ParallaxLayer);
  scroll_speed = Vector2(0, 0);
  file_size = 0;
  grid_count = Vector2(0, 0);
  grid_size = Vector2(0, 0);
}
MapLayer::~MapLayer()
{
}
void MapLayer::load_form_file(Ref<CPtr> &ptr)
{
  int pos = ptr->get_pos();
  ptr->pos_add(40);
  file_size = ptr->read_u32();
  // UtilityFunctions::print(ptr->get_str());
  set_name(ptr->get_str());
  ptr->pos_add(64);
  grid_count.x = ptr->read_u32();
  grid_count.y = ptr->read_u32();
  grid_size.x = ptr->read_u32();
  grid_size.y = ptr->read_u32();
  layer_size = grid_size * grid_count;
  ptr->pos_add(4);
  layer_type = ptr->read_u32();
  scroll_speed.x = ptr->read_u32();
  scroll_speed.y = ptr->read_u32();
  ptr->pos_add(48);
  int group_pos = pos + ptr->read_u32();
  int group_size = ptr->read_u32();
  int c_pos = ptr->get_pos();
  ptr->set_pos(group_pos);
  if (group_size > 0)
  {
    int group_count = ptr->read_u32();
    for (int i = 0; i < group_count; i++)
    {
      GroupObj *group_obj = memnew(GroupObj);
      group_obj->initialize_class();
      group_obj->load(ptr);
      objects.append(group_obj);
    }
  }
  ptr->set_pos(c_pos);
  ptr->pos_add(104);
  if ((ptr->get_pos()+116)!=(pos+file_size))
  {
    int static_obj_count = ptr->read_u32();
    for (int i = 0; i < static_obj_count; i++)
    {
      StaticObj *static_obj = memnew(StaticObj);
      static_obj->initialize_class();
      static_obj->load(ptr);
      objects.append(static_obj);
    }
  }
  objects.sort_custom(callable_mp(this, &MapLayer::static_obj_sort));
  Vector2 map_size = game_map->get_map_size();
  Vector2 view_port_offset = game_map->get_viewport_offset();
  Vector2 motion_scale = Vector2(1, 1);
  float x_scale = (layer_size.x - 800) / ((map_size.x - 1) * 800);
  float y_scale = (layer_size.y - 600) / ((map_size.y - 1) * 600);
  bool is_x_move = false;
  bool is_y_move = false;
  bool is_x_mirroing = false;
  bool is_y_mirroing = false;
  if (layer_type == 0x10001)
  {
    is_x_mirroing = false;
    is_y_mirroing = false;
    is_x_move = true;
    is_y_move = true;
  }
  else if (layer_type == 0x10003)
  {
    is_x_mirroing = true;
    is_y_mirroing = false;
    is_x_move = true;
    is_y_move = false;
  }
  else if (layer_type == 0x20001)
  {
    is_x_mirroing = false;
    is_y_mirroing = false;
    is_x_move = false;
    is_y_move = false;
  }
  // if (layer_type==0x10001){
  //   set_position(view_port_offset*Vector2(x_scale,y_scale));
  //   set_motion_scale(Vector2(x_scale,y_scale));
  // }else if(layer_type==0x10003){

  // }
  Vector2 layer_pos = Vector2(0, 0);
  Vector2 mirroing = Vector2(0, 0);
  layer_pos = -view_port_offset;
  if (is_x_move)
  {
    motion_scale.x = x_scale;
    layer_pos.x *= x_scale;
  }
  if (is_y_move)
  {
    motion_scale.y = y_scale;
    layer_pos.y *= y_scale;
  }
  if (is_x_mirroing)
  {
    mirroing.x = layer_size.x;
  }
  if (is_y_mirroing)
  {
    mirroing.y = layer_size.y;
  }
  if (layer_size.x <= 800)
  {
    layer_pos.x = 0;
    motion_scale.x = 0;
  }
  if (layer_size.y <= 600)
  {
    layer_pos.y = 0;
    motion_scale.y = 0;
  }
  parallax_layer->set_motion_scale(motion_scale);
  parallax_layer->set_position(layer_pos);
  parallax_layer->set_mirroring(mirroing);
  ptr->set_pos(pos);
}
void MapLayer::_physics_process(double delta)
{
  Vector2 pos = get_scroll_offset();
  pos -= delta * scroll_speed;
  set_scroll_offset(pos);
}
Vector2 MapLayer::get_grid_size()
{
  return grid_size;
}
Vector2 MapLayer::get_grid_count()
{
  return grid_count;
}
int MapLayer::get_layer_type()
{
  return layer_type;
}
Vector2 MapLayer::get_scroll_speed()
{
  return scroll_speed;
}
void MapLayer::_ready()
{
  add_child(parallax_layer);
  for (int i = 0; i < objects.size(); i++)
  {
    Object::cast_to<Node2D>(objects[i])->set_z_index(0);
    parallax_layer->add_child(Object::cast_to<Node2D>(objects[i]));
  }
}
bool MapLayer::static_obj_sort(Variant a, Variant b)
{
  return Object::cast_to<MapRenerobj>(a)->render_prority < cast_to<MapRenerobj>(b)->render_prority;
}
void MapLayer::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("get_layer_type"), &MapLayer::get_layer_type);
  ClassDB::bind_method(D_METHOD("get_scroll_speed"), &MapLayer::get_scroll_speed);
  ClassDB::bind_method(D_METHOD("get_grid_count"), &MapLayer::get_grid_count);
  ClassDB::bind_method(D_METHOD("get_grid_size"), &MapLayer::get_grid_size);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "layer_type", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_layer_type");
  ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "scroll_speed", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_scroll_speed");
  ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "grid_count", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_grid_count");
  ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "grid_size", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_grid_size");
}