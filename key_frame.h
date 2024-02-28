#ifndef KEY_FRAME_H
#define KEY_FRAME_H
#include <godot_cpp/classes/ref.hpp>
#include "c_ptr.h"
namespace godot
{
  class KeyFrame : public RefCounted
  {
    GDCLASS(KeyFrame, RefCounted)
  protected:
    static void _bind_methods();
  public:
    KeyFrame();
    ~KeyFrame();
    Vector2 pos;
    Vector2 scale;
    float scalar;
    int interpolation_type;
    Color color;
    float rotation;
    float time; 
    float get_scalar();
    float get_time();
    float get_rotation();
    float get_interpolation_type();
    void load(Ref<CPtr> &ptr);
    int get_key_frame_size();
  };
}
#endif