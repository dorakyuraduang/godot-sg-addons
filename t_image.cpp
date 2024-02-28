#include "t_image.h"
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;
void TImage::_bind_methods()
{
}
TImage::TImage()
{
}
TImage::~TImage()
{
}
void TImage::create_image_a(Ref<CPtr> &ptr)
{
  ani_pos.x = ptr->read_s32();
  ani_pos.y = ptr->read_s32();
  width = ptr->read_u32();
  height = ptr->read_u32();
  ptr->pos_add(4);
  int encode_type = ptr->read_u32();
  Ref<Image> image = Image::create(width, height, false, Image::FORMAT_RGBA8);
  switch (encode_type)
  {
  case 0:
    set_image_data0(ptr, image);
    break;
  case 1:
    set_image_data1(ptr, image);
    break;
  case 2:
    set_image_data2(ptr, image);
    break;
  case 3:
    set_image_data3(ptr, image);
    break;
  case 4:
    set_image_data4(ptr, image);
    break;
  default:
    break;
  }
  offset.x = ptr->read_s32();
  offset.y = ptr->read_s32();
  next_frame_time = ptr->read_u32() / 1000.0;
  copy_from(image);
}
void TImage::create_image_b(Ref<CPtr> &ptr)
{
  offset = Vector2(0, 0);
  width = ptr->read_u32();
  height = ptr->read_u32();
  ptr->pos_add(4);
  int encode_type = ptr->read_u32();
  // Ref<Image> image = Image::create(width, height, false, Image::FORMAT_RGBA8);
  Ref<Image> image = Image::create(width, height, false, Image::FORMAT_RGBA8);
  switch (encode_type)
  {
  case 0:
    set_image_data0(ptr, image);
    break;
  case 1:
    set_image_data1(ptr, image);
    break;
  case 2:
    set_image_data2(ptr, image);
    break;
  case 3:
    set_image_data3(ptr, image);
    break;
  case 4:
    set_image_data4(ptr, image);
    break;
  default:
    break;
  }
  copy_from(image);
}
void TImage::set_image_data0(Ref<CPtr> &ptr, Ref<Image> &image)
{
  for (int h = 0; h < height; h++)
  {
    for (int w = 0; w < width; w++)
    {
      int rgb = ptr->read_u16();
      int r = (rgb >> 10) & 0x1F;
      int g = (rgb >> 5) & 0x1F;
      int b = rgb & 0x1F;
      r = (r << 3) | (r >> 2);
      g = (g << 3) | (g >> 2);
      b = (b << 3) | (b >> 2);
      image->set_pixel(w, h, Color(r / 255.0, g / 255.0, b / 255.0, 1.0));
    }
  }
}
void TImage::set_image_data1(Ref<CPtr> &ptr, Ref<Image> &image)
{
  for (int h = 0; h < height; h++)
  {
    for (int w = 0; w < width; w++)
    {
      int a = ptr->read_u8();
      int b = ptr->read_u8();
      image->set_pixel(w, h, Color(lo(b) / 255.0, hi(a) / 255.0, lo(a) / 255.0, hi(b) / 255.0));
    }
  }
}
void TImage::set_image_data2(Ref<CPtr> &ptr, Ref<Image> &image)
{
  for (int h = 0; h < height; h++)
  {
    for (int w = 0; w < width; w++)
    {
      uint8_t b = ptr->read_u8();
      uint8_t g = ptr->read_u8();
      uint8_t r = ptr->read_u8();
      uint8_t a = ptr->read_u8();
      image->set_pixel(w, h, Color(r / 255.0, g / 255.0, b / 255.0, a / 255.0));
    }
  }
}
void TImage::set_image_data3(Ref<CPtr> &ptr, Ref<Image> &image)
{
  for (int y = 0; y < height; y += 4)
  {
    for (int x = 0; x < width; x += 4)
    {
      Color color1 = decode_etc1(uint16_t(ptr->read_u16()));
      Color color2 = decode_etc1(uint16_t(ptr->read_u16()));
      for (int offset_y = 0; offset_y < 4; offset_y++)
      {
        uint8_t offsets = uint8_t(ptr->read_u8());
        for (int offset_x = 0; offset_x < 4; offset_x++)
        {
          int idx = offset_y * 4 + offset_x;
          int color_idx = (offsets >> (offset_x * 2)) & 0x03;
          Color color;
          if (color_idx == 0)
          {
            color = color1;
          }
          else if (color_idx == 1)
          {
            color = color2;
          }
          else if (color_idx == 2)
          {
            color = interpolateColor(color1, color2);
          }
          else
          {
            color = interpolateColor(color2, color1);
          }
          int p_x = x + offset_x;
          int p_y = y + offset_y;
          if (p_x < width & p_y < height)
          {
            image->set_pixel(p_x,p_y, color);
          }
        }
      }
    }
  }
}
void TImage::set_image_data4(Ref<CPtr> &ptr, Ref<Image> &image)
{
  for (int y = 0; y < height; y += 4)
  {
    for (int x = 0; x < width; x += 4)
    {
      PackedInt32Array alphas;
      for (int b = 0; b < 8; b++)
      {
        alphas.append(ptr->read_u8());
      }
      Color color1 = decode_etc1(uint16_t(ptr->read_u16()));

      Color color2 = decode_etc1(uint16_t(ptr->read_u16()));
      for (int offset_y = 0; offset_y < 4; offset_y++)
      {
        uint8_t offsets = uint8_t(ptr->read_u8());
        for (int offset_x = 0; offset_x < 4; offset_x++)
        {
          int idx = offset_y * 4 + offset_x;
          int color_idx = (offsets >> (offset_x * 2)) & 0x03;
          Color color;
          if (color_idx == 0)
          {
            color = color1;
          }
          else if (color_idx == 1)
          {
            color = color2;
          }
          else if (color_idx == 2)
          {
            color = interpolateColor(color1, color2);
          }
          else
          {
            color = interpolateColor(color2, color1);
          }
          color.a = alphas[idx / 2] / 255.0;
          int p_x = x + offset_x;
          int p_y = y + offset_y;
          if (p_x < width & p_y < height)
          {
            image->set_pixel(p_x, p_y, color);
          }
        }
      }
    }
  }
}
Color TImage::decode_etc1(uint16_t color)
{
  int64_t r, g, b;
  r = (color >> 11) & 0x1F;
  g = (color >> 5) & 0x3F;
  b = color & 0x1F;
  r = (r << 3) | (r >> 2);
  g = (g << 2) | (g >> 4);
  b = (b << 3) | (b >> 2);
  return Color(r / 255.0, g / 255.0, b / 255.0);
}
Color TImage::interpolateColor(Color color1, Color color2)
{
  float r = (color1.r + color2.r) / 2.0;
  float g = (color1.g + color2.g) / 2.0;
  float b = (color1.b + color2.b) / 2.0;
  return Color(r, g, b);
}
float TImage::hi(uint8_t n)
{
  int a = (n & 0xF0) >> 4;
  return (a << 4 | a);
}

float TImage::lo(uint8_t n)
{
  int d = n & 0xF;
  return (d << 4 | d);
}