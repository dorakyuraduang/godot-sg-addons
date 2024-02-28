#ifndef ID_IMAGE_LOADER_H
#define ID_IMAGE_LOADER_H
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_format_loader.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include "id_image.h"
#include "ui_image.h"
using namespace godot;
class ImageLoader : public ResourceFormatLoader
{
  GDCLASS(ImageLoader, ResourceFormatLoader)
public:
  virtual PackedStringArray _get_recognized_extensions() const override;
  virtual bool _handles_type(const StringName &type) const override;
  virtual String _get_resource_type(const String &p_path) const override;
  virtual bool _exists(const String &path) const override;
  virtual Variant _load(const String &path, const String &original_path, bool use_sub_threads, int32_t cache_mode) const override;
  Ref<IdImage> load_id_image(const String &path) const;
  Ref<UiImage> load_ui_image(const String &path) const;
protected:
  static void _bind_methods();
};
#endif