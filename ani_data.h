#ifndef ANI_DATA_H
#define ANI_DATA_H
#include <godot_cpp/classes/ref.hpp>
#include "c_ptr.h"
namespace godot
{
  class AniData : public RefCounted
  {
    GDCLASS(AniData, RefCounted)
  protected:
    static void _bind_methods();

  public:
    int repeat;
    bool follow_path;
    bool attach_to_path;
    bool always_update;
    Array key_frames;
    int spline_path;
    AniData();
    ~AniData();
    Array get_key_frames();
    void load(Ref<CPtr> &ptr);
  };

}
#endif