#ifndef C_PTR_H
#define C_PTR_H
#include <godot_cpp/classes/ref.hpp>
namespace godot
{
  class CPtr : public RefCounted
  {
    GDCLASS(CPtr, RefCounted)
  protected:
    static void _bind_methods();
  public:
    CPtr();
    ~CPtr();
    int read_u32();
    int read_u16();
    int read_u8();
    int read_s32();
    bool read_bool();
    float read_float();
    String get_str();
    int get_pos();
    void set_pos(int offset);
    void pos_add(int offset);
    void set_data(PackedByteArray &data);
  private:
    PackedByteArray data;
    int pos;
  };
}
#endif