#include "register_types.h"
#include "id_image.h"
#include "ui_image.h"
#include "t_image.h"
#include "game_map.h"
#include "spline_mgr.h"
#include "static_obj.h"
#include "spline.h"
#include "line_node.h"
#include "bezier_node.h"
#include "map_layer.h"
#include "ani_data.h"
#include "bezier_node.h"
#include "line_node.h"
#include "key_frame.h"
#include "spline_mgr.h"
#include "group_obj.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/engine.hpp>
#include "c_ptr.h"
#include "image_loader.h"
#include "map_renderableobj.h"
using namespace godot;
Ref<ImageLoader> image_loader;
void initialize_sg_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
	// Engine::get_singleton()->add_singleton(Engine::Singleton("PhysicsServer3DManager", PhysicsServer3DManager::get_singleton(), "PhysicsServer3DManager"));
	ClassDB::register_class<CPtr>();
	ClassDB::register_class<ImageLoader>();
	ClassDB::register_class<UiImage>();
	ClassDB::register_class<IdImage>();
	ClassDB::register_class<TImage>();
	ClassDB::register_class<MapRenerobj>();
	ClassDB::register_class<Spline>();
	ClassDB::register_class<LineNode>();
	ClassDB::register_class<BezierNode>();
	ClassDB::register_class<MapLayer>();
	ClassDB::register_class<StaticObj>();
	ClassDB::register_class<GameMap>();
	ClassDB::register_class<AniData>();
	ClassDB::register_class<GroupObj>();
	ClassDB::register_class<KeyFrame>();
	image_loader.instantiate();
	SplineMgr::instance();
	// SplineMgr();
	ResourceLoader::get_singleton()->add_resource_format_loader(image_loader);
}

void uninitialize_sg_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
	ResourceLoader::get_singleton()->remove_resource_format_loader(image_loader);
}

extern "C"
{
	// Initialization.
	GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(initialize_sg_module);
		init_obj.register_terminator(uninitialize_sg_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}