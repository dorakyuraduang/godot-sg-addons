#include "image_loader.h"
#include "c_ptr.h"
#include <godot_cpp/variant/utility_functions.hpp>
String ImageLoader::_get_resource_type(const String &path) const
{
    if (path.get_extension() == "gsn")
    {
        return "IdImage";
    }
    if (path.get_extension() == "gso")
    {
        return "IdImage";
    }
    if (path.get_extension() == "gsa")
    {
        return "UiImage";
    }
    return "";
}
PackedStringArray ImageLoader::_get_recognized_extensions() const
{
    PackedStringArray arr;
    arr.push_back("gsn");
    arr.push_back("gso");
    arr.push_back("gsa");
    // arr.push_back("gsa");
    return arr;
}
bool ImageLoader::_handles_type(const StringName &type) const
{
    return type == StringName("Texture2D");
}
bool ImageLoader::_exists(const String &path) const
{
    return FileAccess::file_exists(path);
}

Variant ImageLoader::_load(const String &path, const String &original_path, bool use_sub_threads, int32_t cache_mode) const
{
    if (path.ends_with("gsn") || path.ends_with("gso"))
    {
        return load_id_image(path);
    }else if(path.ends_with("gsa")){
        return load_ui_image(path);
    }
    return nullptr;
}
void ImageLoader::_bind_methods()
{
}
Ref<IdImage> ImageLoader::load_id_image(const String &path) const
{
    Ref<IdImage> id_image;
    PackedByteArray data = FileAccess::get_file_as_bytes(path);
    Ref<CPtr> c_ptr;
    c_ptr.instantiate();
    c_ptr->set_data(data);
    id_image.instantiate();
    id_image->load_image_file(c_ptr);
    return id_image;
}

Ref<UiImage> ImageLoader::load_ui_image(const String &path) const
{
    Ref<UiImage> ui_image;
    PackedByteArray data = FileAccess::get_file_as_bytes(path);
    Ref<CPtr> c_ptr;
    c_ptr.instantiate();
    c_ptr->set_data(data);
    ui_image.instantiate();
    ui_image->load_image_file(c_ptr);
    return ui_image;
}