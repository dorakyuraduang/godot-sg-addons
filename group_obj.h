#ifndef GROUP_OBJ_H
#define GROUP_OBJ_H
#include "c_ptr.h"
#include "map_renderableobj.h"
namespace godot
{
  class GroupObj : public MapRenerobj
  {
    GDCLASS(GroupObj, MapRenerobj)
  protected:
    static void _bind_methods();

  public:
    GroupObj();
    ~GroupObj();
    void load(Ref<CPtr> &ptr);
    void set_effect(int value);
    void load_all_static_obj(String path);
    Rect2 fixed_bound;
    Vector2 render_center;
    Array objects;
    bool objects_sort(Variant a, Variant b);
    void _ready() override;

  private:
  };
}
#endif