#include "spline_mgr.h"
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;
SplineMgr *SplineMgr::singleton = nullptr;
void SplineMgr::instance()
{
  if (singleton == nullptr)
  {
    singleton = new SplineMgr();
  }
}
SplineMgr::SplineMgr()
{
  singleton = this;
}
SplineMgr::~SplineMgr()
{
  if (singleton != nullptr)
  {
    delete singleton;
  }
  singleton = nullptr;
}
SplineMgr *SplineMgr::get_singleton()
{
  return singleton;
}
void SplineMgr::add_spline(int id, Ref<Spline> &line)
{
  splines[id] = line;
}
void SplineMgr::clear_splint()
{
  splines.clear();
}
Ref<Spline> SplineMgr::get_spline(int id)
{
  return splines[id];
}
void SplineMgr::_bind_methods()
{
}