#ifndef MAP_RENERABLEOBJ_H
#define MAP_RENERABLEOBJ_H
#include <godot_cpp/classes/sprite2d.hpp>
namespace godot
{
  class MapRenerobj : public Sprite2D
  {
    GDCLASS(MapRenerobj, Sprite2D)
  protected:
    static void _bind_methods();

  public:
    int render_prority;
    MapRenerobj();
    ~MapRenerobj();
  protected:
  };
}
#endif