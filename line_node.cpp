#include "line_node.h"
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;
LineNode::LineNode()
{
}
LineNode::~LineNode()
{
}
void LineNode::load(Ref<CPtr> &ptr)
{
  ptr->pos_add(4);
  // UtilityFunctions::print(ptr->read_u32());
  x = ptr->read_u32();
  y = ptr->read_u32();
}
void LineNode::_bind_methods(){
  
}