#ifndef UI_IMAGE_H
#define UI_IMAGE_H
#include "t_image.h"
#include "c_ptr.h"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/image_texture.hpp>
namespace godot
{
	class UiImage : public ImageTexture
	{
		GDCLASS(UiImage, ImageTexture)

	protected:
		static void _bind_methods();

	public:
		UiImage();
		~UiImage();
		int frames;
		void clear_data();
		int frame;
		int get_frame();
		void set_frame(int value);
		int get_frames();
		void set_frames(int value);
		Array images;
		void load_image_file(Ref<CPtr> &ptr);
	};
}
#endif