#ifndef BEZIER_NODE
#define BEZIER_NODE
#include "c_ptr.h"
#include <godot_cpp/classes/ref.hpp>
namespace godot
{
  class BezierNode : public RefCounted
  {
    GDCLASS(BezierNode, RefCounted)
  protected:
    static void _bind_methods();

  private:
  public:
    int x1;
    int y1;
    int x2;
    int y2;
    void load(Ref<CPtr> &ptr);
    BezierNode();
    ~BezierNode();
  };
}
#endif