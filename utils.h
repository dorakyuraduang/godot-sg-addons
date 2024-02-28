#ifndef UTILS_H
#define UTILS_H
#include <godot_cpp/variant/color.hpp>
namespace godot
{
  class Utils
  {
  public:
    static Color hex_to_color(int hex);
  };
}

#endif