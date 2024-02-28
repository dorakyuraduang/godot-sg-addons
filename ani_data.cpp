#include "ani_data.h"
#include "key_frame.h"
using namespace godot;
AniData::AniData()
{
}
AniData::~AniData()
{
}
Array AniData::get_key_frames()
{
  return key_frames;
}
void AniData::load(Ref<CPtr> &ptr)
{
  ptr->pos_add(8);
  int frames = ptr->read_s32();
  attach_to_path = ptr->read_bool();
  follow_path = ptr->read_bool();
  repeat = ptr->read_bool();
  always_update = ptr->read_bool();
  spline_path = ptr->read_u32();
  for (int i = 0; i < frames; i++)
  {
    Ref<KeyFrame> key_frame;
    key_frame.instantiate();
    key_frame->load(ptr);
    key_frames.append(key_frame);
  }
}
void AniData::_bind_methods()
  {
    ClassDB::bind_method(D_METHOD("get_key_frames"), &AniData::get_key_frames);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "key_frames", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_READ_ONLY), "", "get_key_frames");
  }