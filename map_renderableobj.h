// #ifndef MAP_RENERABLEOBJ_H
// #ifndef MAP_RENERABLEOBJ_H
// #include <godot_cpp/classes/texture.hpp>
// #include <godot_cpp/classes/node2d.hpp>
// namespace godot
// {
//   class MapRenerobj : public Node2D
//   {
//     GDCLASS(SgSprite, Node2D);
//     Ref<Texture2D> texture;
//     Ref<Gsn> gsn;
//     Point2 offset;
//     int frame = 0;
//     int frames=0;
//     real_t frame_progress = 0.0;
//     void _texture_changed();
//     bool playing;
//   public:
//     SgSprite();
//     void set_texture(const Ref<Texture2D> &p_texture);
//     Ref<Texture2D> get_texture() const;
//     void set_gsn(const Ref<Gsn> &p_gsn);
//     Ref<Gsn> get_gsn() const;
//     void set_frame(int value);
//     int get_frame();
//     void set_playing(bool value);
//     bool get_playing();
//   protected:
//     void _notification(int p_what);
//     static void _bind_methods();
//   };
// }
// #endif