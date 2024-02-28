// #include "sg_sprite.h"
// #include <godot_cpp/variant/utility_functions.hpp>
// #include "math.h"
// using namespace godot;
// void SgSprite::set_texture(const Ref<Texture2D> &p_texture)
// {
//   if (p_texture == texture)
//   {
//     return;
//   }
//   offset = Vector2(0,0);
//   offset += gsn->ani_pos[frame];
//   offset -=gsn->offsets[frame];

//   // offset+=gsn->bound_info.position-gsn->bound_info.size;
//   // offset.x-=(gsn->bound_info.size.x/2-gsn->bound_info.position.x);
//   // offset.y-=(gsn->bound_info.size.y/2-gsn->bound_info.position.y)/2.0;
//   texture = p_texture;
//   queue_redraw();
// }
// void SgSprite::_bind_methods()
// {
//   ClassDB::bind_method(D_METHOD("set_gsn", "gsn"), &SgSprite::set_gsn);
//   ClassDB::bind_method(D_METHOD("get_gsn"), &SgSprite::get_gsn);
//   ClassDB::bind_method(D_METHOD("set_frame", "frame"), &SgSprite::set_frame);
//   ClassDB::bind_method(D_METHOD("get_frame"), &SgSprite::get_frame);
//   ClassDB::bind_method(D_METHOD("set_playing", "playing"), &SgSprite::set_playing);
//   ClassDB::bind_method(D_METHOD("get_playing"), &SgSprite::get_playing);
//   ClassDB::bind_method(D_METHOD("set_texture", "texture"), &SgSprite::set_texture);
//   ClassDB::bind_method(D_METHOD("get_texture"), &SgSprite::get_texture);
//   ADD_PROPERTY(PropertyInfo(Variant::INT, "frame", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR), "set_frame", "get_frame");
//   ADD_PROPERTY(PropertyInfo(Variant::BOOL, "playing", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_EDITOR), "set_playing", "get_playing");
//   ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "gsn", PROPERTY_HINT_RESOURCE_TYPE, "Gsn"), "set_gsn", "get_gsn");
//   ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D", PROPERTY_USAGE_READ_ONLY), "set_texture", "get_texture");
// }
// void SgSprite::set_playing(bool value)
// {
//   playing = value;
//   set_process_internal(playing);
// }
// bool SgSprite::get_playing()
// {
//   return playing;
// }
// void SgSprite::_notification(int p_what)
// {
//   switch (p_what)
//   {
//   case NOTIFICATION_DRAW:
//   {
//     if (texture.is_null())
//     {
//       return;
//     }
//     RID ci = get_canvas_item();
//     texture->draw(ci, offset);
//   }
//   break;
//   case NOTIFICATION_INTERNAL_PROCESS:
//   {

//     if (gsn.is_null())
//     {
//       return;
//     }
//     if (!gsn->is_anime)
//     {
//       return;
//     }
//     double remaining = get_process_delta_time();
//     int i = 0;
//     while (remaining)
//     {
//       double speed = 1000.0 / gsn->next_frame_times[frame];
//       double abs_speed = Math::abs(speed);
//       if (speed == 0)
//       {
//         return; // Do nothing.
//       }
//       int last_frame = frames - 1;
//       // Frame count may be changed by animation_finished or frame_changed signals.
//       if (!signbit(speed))
//       {
//         // Forwards.
//         if (frame_progress >= 1.0)
//         {
//           if (frame >= last_frame)
//           {
//             set_frame(0);
//           }
//           else
//           {
//             frame++;
//             set_frame(frame);
//           }
//           frame_progress = 0.0;
//           queue_redraw();
//         }
//         double to_process = MIN((1.0 - frame_progress) / abs_speed, remaining);
//         frame_progress += to_process * abs_speed;
//         remaining -= to_process;
//       }
//       else
//       {
//         // Backwards.
//         if (frame_progress <= 0)
//         {
//           if (frame <= 0)
//           {
//             set_frame(last_frame);
//           }
//           else
//           {
//             frame--;
//             set_frame(frame);
//           }
//           frame_progress = 1.0;
//         }
//         double to_process = MIN(frame_progress / abs_speed, remaining);
//         frame_progress -= to_process * abs_speed;
//         remaining -= to_process;
//       }
//       i++;
//       if (i > frames)
//       {
//         return; // Prevents freezing if to_process is each time much less than remaining.
//       }
//     }
//   }
//   break;
//   }
// }
// Ref<Texture2D> SgSprite::get_texture() const
// {
//   return texture;
// }
// void SgSprite::set_gsn(const Ref<Gsn> &p_gsn)
// {
//   frame = 0;
//   gsn = p_gsn;
//   if (gsn.is_valid())
//   {
//     set_texture(gsn->images[0]);
//     frames = gsn->frames;
//   }
//   else
//   {
//     frames = 0;
//     texture.unref();
//   }
//   queue_redraw();
// }
// Ref<Gsn> SgSprite::get_gsn() const
// {
//   return gsn;
// }
// void SgSprite::set_frame(int value)
// {
//   if (gsn.is_valid())
//   {
//     frame = Math::clamp(value, 0, gsn->frames - 1);
//     set_texture(gsn->images[frame]);
//   }
//   else
//   {
//     frame = 0;
//   }
// }
// int SgSprite::get_frame()
// {
//   return frame;
// }
// SgSprite::SgSprite()
// {
//   set_playing(false);
// }