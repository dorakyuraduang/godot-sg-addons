#ifndef ID_IMAGE_H
#define ID_IMAGE_H
#include "t_image.h"
#include "c_ptr.h"
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/image_texture.hpp>
namespace godot
{
	class IdImage : public ImageTexture
	{
		GDCLASS(IdImage, ImageTexture)

	protected:
		static void _bind_methods();

	public:
		IdImage();
		~IdImage();
		int frames;
		void clear_data();
		int frame;
		int get_frame();
		void set_frame(int value);
		int get_frames();
		void set_frames(int value);
		// Ref<TImage> get_texture() const;
		// void set_texture(const Ref<TImage> &p_image);
		Array images;
		Rect2 bound_info;
		Rect2 clip_info;
		void load_image_file(Ref<CPtr> &ptr);
	};
}
#endif