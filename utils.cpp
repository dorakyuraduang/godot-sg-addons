#include "utils.h"
using namespace godot;
Color Utils::hex_to_color(int hex)
{
  float b = ((hex >> 0) & 0xff) / 255.0;
  float g = ((hex >> 8) & 0xff) / 255.0;
  float r = ((hex >> 16) & 0xff) / 255.0;
  float a = ((hex >> 24) & 0xff) / 255.0;
  return Color(r, g, b, a);
}