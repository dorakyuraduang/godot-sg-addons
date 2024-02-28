#include "id_image.h"
using namespace godot;
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <t_image.h>
IdImage::IdImage()
{
}
IdImage::~IdImage()
{
}
void IdImage::_bind_methods()
{
  // ClassDB::bind_method(D_METHOD("set_data", "data"), &IdImage::set_data);
  // ClassDB::bind_method(D_METHOD("get_data"), &IdImage::get_data);
  ClassDB::bind_method(D_METHOD("set_frames", "frames"), &IdImage::set_frames);
  ClassDB::bind_method(D_METHOD("get_frames"), &IdImage::get_frames);
  ClassDB::bind_method(D_METHOD("set_frame", "frame"), &IdImage::set_frame);
  ClassDB::bind_method(D_METHOD("get_frame"), &IdImage::get_frame);
  // ClassDB::bind_method(D_METHOD("get_texture"), &IdImage::get_texture);
  // ClassDB::bind_method(D_METHOD("set_texture"), &IdImage::set_texture);
  // ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, ""), "set_texture", "get_texture");
  // ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "offsets", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR), "set_offsets", "get_offsets");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "frame", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR), "set_frame", "get_frame");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "frames", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "set_frames", "get_frames");
  // ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_data", "get_data");
}
void IdImage::clear_data()
{
  frames=0;
  frame = 0;
  images.clear();
}
int IdImage::get_frames()
{
  return frames;
}
void IdImage::set_frames(int value)
{
  frames = value;
}
void IdImage::set_frame(int value)
{
  frame = Math::clamp(value, 0, frames - 1);
  set_image(images[frame]);
}
int IdImage::get_frame()
{
  return frame;
}
void IdImage::load_image_file(Ref<CPtr> &ptr)
{
  clear_data();
  ptr->pos_add(16);
  set_frames(ptr->read_u32());
  ptr->pos_add(4);
  bound_info.size.x =ptr->read_u32();
  bound_info.size.y =ptr->read_u32();
  bound_info.position.x = ptr->read_u32();
  bound_info.position.y = ptr->read_u32();
  clip_info.size.x = ptr->read_u32();
  clip_info.size.y = ptr->read_u32();
  clip_info.position.x = ptr->read_u32();
  clip_info.position.y = ptr->read_u32();
  for (int i = 0; i < frames; i++)
  {
    Ref<TImage> t_image;
    // UtilityFunctions::print(file->get_position());
    t_image.instantiate();
    t_image->create_image_a(ptr);
    images.append(t_image);
  }
  set_frame(0);
}
// void IdImage::set_texture(const Ref<TImage> &p_texture)
// {
  
//   texture = p_texture;
// }
// Ref<TImage> IdImage::get_texture() const
// {
//   return texture;
// }