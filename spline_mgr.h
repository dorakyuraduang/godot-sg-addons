#ifndef SPLINE_MGT_H
#define SPLINE_MGT_H
#include "spline.h"
namespace godot
{
  class SplineMgr : public Object
  {
    GDCLASS(SplineMgr, Object)
    static SplineMgr *singleton;

  protected:
    static void _bind_methods();

  public:
    static SplineMgr *get_singleton();
    void add_spline(int id, Ref<Spline> &line);
    void clear_splint();
    SplineMgr();
    ~SplineMgr();
    static void instance();
    Ref<Spline> get_spline(int id);
  private:
    Dictionary splines;
  };
}
#endif
