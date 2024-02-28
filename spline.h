#ifndef SPLINE_H
#define SPLINE_H
#include "c_ptr.h"
#include "bezier_node.h"
#include "line_node.h"
#include <godot_cpp/classes/ref.hpp>
namespace godot
{
  class Spline : public RefCounted
  {
    GDCLASS(Spline,RefCounted)
  protected:
    static void _bind_methods();
  public:
    int id;
    Array nodes;
    Spline();
    ~Spline();
    void load(Ref<CPtr> &ptr);
    Vector2 get_pos(double scalar);
    Vector2 get_line_pos(double scalar);
    Vector2 get_bezier_pos(double scalar);
  private:
    int node_type;
    
  };
}
#endif