#include "ui_image.h"
#include <cmath>
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;
UiImage::UiImage()
{
}
UiImage::~UiImage()
{
}
void UiImage::load_image_file(Ref<CPtr> &ptr)
{
  clear_data();
  ptr->pos_add(16);
  int image_width = ptr->read_u32();
  int image_height = ptr->read_u32();
  int width = ptr->read_u32();
  int height =ptr->read_u32();
  frames = ptr->read_u32();
  for (int i = 0; i < frames; i++)
  {
    Ref<Image> ani_image = Image::create(width, height, false, Image::FORMAT_RGBA8);

    int x = std::ceil(float(width) / float(image_width));
    int y = std::ceil(float(height) / float(image_height));
    for (int h = 0; h < y; h++)
    {
      for (int w = 0; w < x; w++)
      {
        Ref<TImage> image;
        image.instantiate();
        image->create_image_b(ptr);
        ani_image->blit_rect(image, Rect2i(0, 0, width, height), Vector2(image_width * w, image_height * h));
      }
    }
    images.append(ani_image);
  }
  set_frame(0);
}
void UiImage::clear_data()
{
  frames = 0;
  frame = 0;
  images.clear();
}
int UiImage::get_frames()
{
  return frames;
}
void UiImage::set_frames(int value)
{
  frames = value;
}
void UiImage::set_frame(int value)
{
  frame = Math::clamp(value, 0, frames - 1);
  set_image(images[frame]);
}
int UiImage::get_frame()
{
  return frame;
}

void UiImage::_bind_methods()
{
  // ClassDB::bind_method(D_METHOD("set_data", "data"), &IdImage::set_data);
  // ClassDB::bind_method(D_METHOD("get_data"), &IdImage::get_data);
  ClassDB::bind_method(D_METHOD("set_frames", "frames"), &UiImage::set_frames);
  ClassDB::bind_method(D_METHOD("get_frames"), &UiImage::get_frames);
  ClassDB::bind_method(D_METHOD("set_frame", "frame"), &UiImage::set_frame);
  ClassDB::bind_method(D_METHOD("get_frame"), &UiImage::get_frame);
  ADD_PROPERTY(PropertyInfo(Variant::INT, "frame", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR), "set_frame", "get_frame");
  ADD_PROPERTY(PropertyInfo(Variant::INT, "frames", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "set_frames", "get_frames");
  // ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "data", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_data", "get_data");
}