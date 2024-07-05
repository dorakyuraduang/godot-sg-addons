#include "base_status_data.h"
using namespace godot;
BaseStatusData::BaseStatusData()
{
  m_nBaseId = 0;
  m_szName = "";
  m_szDescribe = "";
  m_nIcon = 0;
  m_nEffect = 0;
  m_nLastTime = 0;
  m_nTypeId = 0;
  m_nSubTypeId = 0;
  m_nTypeLv = 0;
}
BaseStatusData::~BaseStatusData()
{
}

void BaseStatusData::_bind_methods()
{
}