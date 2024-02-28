#include "bezier_node.h"
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;
BezierNode::BezierNode()
{
}
BezierNode::~BezierNode()
{
}
void BezierNode::load(Ref<CPtr> &ptr)
{
  ptr->pos_add(4);
  x2 = ptr->read_u32();
  y2 = ptr->read_u32();
  x1 = ptr->read_u32();
  y1 = ptr->read_u32();
  ptr->pos_add(1);
}
void BezierNode::_bind_methods()
{
}