#include "spline.h"
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;

Spline::Spline()
{
}
Spline::~Spline()
{
}
void Spline::load(Ref<CPtr> &ptr)
{
  node_type = ptr->read_u32();
  id = ptr->read_u32();

  int str_len = ptr->read_u32();
  ptr->pos_add(str_len);
  int point_count = ptr->read_u32();
  // UtilityFunctions::print(point_count);
  if (point_count > 0)
  {
    for (int i = 0; i < point_count; i++)
    {
      if (node_type == 1)
      {
        Ref<BezierNode> node;
        node.instantiate();
        node->load(ptr);
        nodes.append(node);
      }
      else if (node_type == 3)
      {
        Ref<LineNode> node;
        node.instantiate();
        node->load(ptr);
        nodes.append(node);
        // UtilityFunctions::print(node->x);
      }
    }
  }
}
void Spline::_bind_methods()
{
}
Vector2 Spline::get_pos(double scalar)
{
  if (node_type == 1)
  {
    return get_bezier_pos(scalar);
    
  }
  else if (node_type == 3)
  {
    return get_line_pos(scalar);
  }
  return Vector2();
}
Vector2 Spline::get_line_pos(double scalar)
{

  Ref<LineNode> line1 = Object::cast_to<LineNode>(nodes[0]);
  Ref<LineNode> line2 = Object::cast_to<LineNode>(nodes[1]);
  int x = double(line1->x + (line2->x - line1->x) * scalar);
  int y = double(line1->y + (line2->y - line1->y) * scalar);
  return Vector2(x, y);
}
Vector2 Spline::get_bezier_pos(double scalar)
{
  Ref<BezierNode> line1 = Object::cast_to<BezierNode>(nodes[0]);
  Ref<BezierNode> line2 = Object::cast_to<BezierNode>(nodes[1]);
  Vector2 p0 = Vector2(line1->x1, line1->y1);
  Vector2 p1 = Vector2(line1->x2, line1->y2);
  Vector2 p2 = Vector2(line2->x1, line2->y1);
  Vector2 p3 = Vector2(line2->x2, line2->y2);
  Vector2 q0 = p0.lerp(p1, scalar);
  Vector2 q1 = p1.lerp(p2, scalar);
  Vector2 q2 = p2.lerp(p3, scalar);
  Vector2 r0 = q0.lerp(q1, scalar);
  Vector2 r1 = q1.lerp(q2, scalar);
  Vector2 s = r0.lerp(r1, scalar);
  return s;
}