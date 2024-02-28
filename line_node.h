#ifndef LINE_NODE_H
#define LINE_NODE_H
#include "c_ptr.h"
#include <godot_cpp/classes/ref.hpp>
namespace godot
{
  class LineNode : public RefCounted
  {
    GDCLASS(LineNode, RefCounted)
  protected:
    static void _bind_methods();

  private:
  public:
    int x;
    int y;
    void load(Ref<CPtr> &ptr);
    LineNode();
    ~LineNode();
  };
}
#endif