#ifndef BASE_STATUS_DATA
#define BASE_STATUS_DATA
#include <godot_cpp/classes/ref.hpp>
namespace godot
{
  class BaseStatusData : public RefCounted
  {
    GDCLASS(BaseStatusData, RefCounted)
  protected:
    static void _bind_methods();

  private:
    int m_nBaseId;
    String m_szName;
    String m_szDescribe;
    int m_nIcon;
    int m_nEffect;
    int m_nLastTime;
    int m_nTypeId;
    int m_nSubTypeId;
    int m_nTypeLv;
    PackedInt32Array m_nParam;

  public:
    BaseStatusData();
    ~BaseStatusData();
  };
}
#endif