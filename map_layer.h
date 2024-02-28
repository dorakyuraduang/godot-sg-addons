#ifndef MAP_LAYER_H
#define MAP_LAYER_H
#include "game_map.h"
#include "c_ptr.h"
#include "static_obj.h"
#include <godot_cpp/classes/parallax_layer.hpp>
#include <godot_cpp/classes/parallax_background.hpp>
namespace godot
{
  class MapLayer : public ParallaxBackground
  {
    GDCLASS(MapLayer, ParallaxBackground)
  protected:
    static void _bind_methods();

  private:
  public:
    GameMap *game_map;
    Vector2 grid_count;
    ParallaxLayer *parallax_layer;
    int layer_type;
    Vector2 scroll_speed;
    Vector2 grid_size;
    int file_size;
    MapLayer();
    Array static_objects;
    ~MapLayer();
    void load_form_file(Ref<CPtr> &ptr);
    virtual void _ready() override;
    Vector2 get_grid_size();
    Vector2 get_grid_count();
    int get_layer_type();
    Vector2 layer_size;
    Vector2 get_scroll_speed();
    bool static_obj_sort(Variant a, Variant b);
    virtual void _physics_process(double delta) override;
  };
}
#endif