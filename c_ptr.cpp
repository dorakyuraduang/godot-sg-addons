#include "c_ptr.h"
using namespace godot;
CPtr::CPtr()
{
  pos = 0;
}
CPtr::~CPtr()
{
}
int CPtr::read_u32()
{
  int u32 = data.decode_u32(pos);
  pos += 4;
  return u32;
}
int CPtr::read_s32()
{
  int s32 = data.decode_s32(pos);
  pos += 4;
  return s32;
}
int CPtr::read_u16()
{
  int u16 = data.decode_u16(pos);
  pos += 2;
  return u16;
}
int CPtr::read_u8()
{
  int u8 = data.decode_u8(pos);
  pos += 1;
  return u8;
}
float CPtr::read_float(){
  float f = data.decode_float(pos);
  pos += 4;
  return f;
}
bool CPtr::read_bool(){
  bool b=bool(read_u8());
  return b;

}
String CPtr::get_str()
{
  PackedByteArray chars;
  int u32=1;
  int offset=0;
  while (u32)
  {
    
    for (int i = 0; i < 4; i++)
    {
      u32 = 0;
      int chr = data.decode_s8(pos+offset);
      chars.append(chr);
      u32 += chr;
      offset+=1;
    }
  }
  return chars.get_string_from_ascii();
}
void CPtr::set_data(PackedByteArray &p_data)
{
  data = p_data;
}
void CPtr::pos_add(int offset)
{
  pos += offset;
}
void CPtr::set_pos(int offset)
{
  pos = offset;
}
int CPtr::get_pos()
{
  return pos;
}
void CPtr::_bind_methods()
{
}