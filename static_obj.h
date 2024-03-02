#ifndef STATIC_OBJ_H
#define STATIC_OBJ_H
#include "map_renderableobj.h"
#include "c_ptr.h"
#include "id_image.h"
#include "ani_data.h"
namespace godot
{
  class StaticObj : public MapRenerobj
  {
    GDCLASS(StaticObj, MapRenerobj)
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
    void set_effect(int value);
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