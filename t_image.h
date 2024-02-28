#ifndef T_IMAGE_H
#define T_IMAGE_H
#include "c_ptr.h"
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/file_access.hpp>
namespace godot
{
  class TImage : public Image
  {
    GDCLASS(TImage,Image)
  protected:
    static void _bind_methods();

  public:
    TImage();
    ~TImage();
    Vector2 offset;
    Vector2 ani_pos;
    int width;
    int height;
    double next_frame_time;
    Color interpolateColor(Color color1, Color color2);
		Color decode_etc1(uint16_t color);
    void create_image_a(Ref<CPtr> &ptr);
    void create_image_b(Ref<CPtr> &ptr);
    void set_image_data0(Ref<CPtr> &ptr,Ref<Image> &image);
    void set_image_data1(Ref<CPtr> &ptr,Ref<Image> &image);
    void set_image_data2(Ref<CPtr> &ptr,Ref<Image> &image);
    void set_image_data3(Ref<CPtr> &ptr,Ref<Image> &image);
    void set_image_data4(Ref<CPtr> &ptr,Ref<Image> &image);
    float hi(uint8_t n);
    float lo(uint8_t n);
  };
}
#endif
