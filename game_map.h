#ifndef GAME_MAP_H
#define GAME_MAP_H
#include "c_ptr.h"
#include "spline_mgr.h"
#include <godot_cpp/classes/node2d.hpp>
namespace godot
{
	class GameMap : public Node2D
	{
		GDCLASS(GameMap, Node2D)

	protected:
		static void _bind_methods();

	public:
    GameMap();
    ~GameMap();
		void set_file_path(const String &path);
		String get_file_path() const;
		void load_form_file(String path);
		virtual void _ready() override;
		Array layers;
		Vector2 get_viewport_offset();
		Vector2 get_map_size();
	private:
		String file_path;
		Vector2 map_size;
		Vector2 viewport_offset;
  };
}
#endif