#include "game_map.h"
#include "spline.h"
#include "map_layer.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/engine.hpp>
using namespace godot;
GameMap::GameMap()
{
}
GameMap::~GameMap()
{
}
void GameMap::_ready()
{
  if (!Engine::get_singleton()->is_editor_hint())
  {
    load_form_file(file_path);
  }
}
void GameMap::load_form_file(String path)
{

  PackedByteArray data = FileAccess::get_file_as_bytes(path);
  Ref<CPtr> ptr;
  ptr.instantiate();
  ptr->set_data(data);
  ptr->pos_add(40);
  map_size.x = ptr->read_u32();
  map_size.y = ptr->read_u32();
  ptr->pos_add(12);
  int layer_count = ptr->read_u32();
  viewport_offset.x = ptr->read_u32();
  viewport_offset.y = ptr->read_u32();
  ptr->pos_add(4);
  int next_pos = ptr->read_u32();
  ptr->pos_add(4);
  int spline_pos = ptr->read_u32();
  int spline_size = ptr->read_u32();
  ptr->set_pos(spline_pos);
  while (ptr->get_pos() < (spline_pos + spline_size))
  {
    Ref<Spline> spline;
    spline.instantiate();
    spline->load(ptr);
    SplineMgr::get_singleton()->add_spline(spline->id, spline);
  }

  ptr->set_pos(next_pos);
  for (int i = 0; i < layer_count; i++)
  {
    MapLayer *layer = memnew(MapLayer);
    layer->game_map = this;
    layer->initialize_class();
    layer->load_form_file(ptr);

    add_child(layer);
    if (i < layer_count)
    {
      ptr->pos_add(layer->file_size);
    }
  }
  // UtilityFunctions::print(6);
}
void GameMap::set_file_path(const String &path)
{
  file_path = path;
}
String GameMap::get_file_path() const
{
  return file_path;
}
Vector2 GameMap::get_viewport_offset()
{
  return viewport_offset;
}
Vector2 GameMap::get_map_size()
{
  return map_size;
}
void GameMap::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("set_file_path", "file_path"), &GameMap::set_file_path);
  ClassDB::bind_method(D_METHOD("get_file_path"), &GameMap::get_file_path);
  ClassDB::bind_method(D_METHOD("get_map_size"), &GameMap::get_map_size);
  ClassDB::bind_method(D_METHOD("get_viewport_offset"), &GameMap::get_viewport_offset);
  ADD_PROPERTY(PropertyInfo(Variant::STRING, "file_path", PROPERTY_HINT_FILE, "*.map"), "set_file_path", "get_file_path");
  ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "map_size", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_map_size");
  ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "viewport_offset", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_viewport_offset");
}