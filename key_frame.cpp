#include "key_frame.h"
#include "utils.h"
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;
KeyFrame::KeyFrame()
{
}
KeyFrame::~KeyFrame()
{
}
void KeyFrame::load(Ref<CPtr> &ptr)
{
  pos.x = ptr->read_s32();
  pos.y = ptr->read_s32();
  rotation = ptr->read_float();
  color = Utils::hex_to_color(ptr->read_u32());
  scale.x = ptr->read_float();
  scale.y = ptr->read_float();
  interpolation_type = ptr->read_u32();
  scalar = ptr->read_float();
  time = ptr->read_s32() / 1000.0;
}
int KeyFrame::get_key_frame_size()
{
  return 0x24;
}
float KeyFrame::get_scalar()
{
  return scalar;
}
float KeyFrame::get_time()
{
  return time;
}
float KeyFrame::get_rotation()
{
  return rotation;
}
float KeyFrame::get_interpolation_type()
{
  return interpolation_type;
}
void KeyFrame::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("get_scalar"), &KeyFrame::get_scalar);
  ClassDB::bind_method(D_METHOD("get_time"), &KeyFrame::get_time);
  ClassDB::bind_method(D_METHOD("get_rotation"), &KeyFrame::get_rotation);
  ClassDB::bind_method(D_METHOD("get_interpolation_type"), &KeyFrame::get_interpolation_type);
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "scalar", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_scalar");
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "time", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_time");
  ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "rotation", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_rotation");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "interpolation_type", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_interpolation_type");
}