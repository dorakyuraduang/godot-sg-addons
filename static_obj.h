#ifndef STATIC_OBJ_H
#define STATIC_OBJ_H
#include <godot_cpp/classes/sprite2d.hpp>
#include "c_ptr.h"
#include "id_image.h"
#include "ani_data.h"
namespace godot
{
  class StaticObj : public Sprite2D
  {
    GDCLASS(StaticObj, Sprite2D)
  protected:
    static void _bind_methods();

  private:
    Rect2 fixed_bound;
    Vector2 render_center;
    Vector2 image_center;
    double ani_time;
    double frame_time; 
    void set_frame(int f);

  public:
    StaticObj();
    ~StaticObj();
    int frame;
    int ani_frame;
    int file_size;
    int render_prority;
    void set_effect(int value);
    void set_color(int value);
    void load(Ref<CPtr> &ptr);
    void load_ani_data(Ref<CPtr> &ptr);
    virtual void _ready() override;
    virtual void _physics_process(double delta) override;
    Ref<IdImage> id_image;
    Ref<AniData> ani_data;
    Ref<AniData> get_ani_data();
    void ani_start();
    void ani_frame_end();
    void ani_end();
    void ani_play();
  };
}
#endif