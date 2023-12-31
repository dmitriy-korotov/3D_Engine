#include <editor_app.hpp>

#include <engine/logging/log.hpp>

#include <engine/input/keyboard.hpp>

#include <engine/ecs/ecs_system.hpp>
#include <engine/scene/components/physic.hpp>
#include <engine/scene/components/markers.hpp>
#include <engine/scene/components/render.hpp>

#include <engine/scene/systems/physic/camera_update.hpp>
#include <engine/scene/systems/UI/selected_object_UI.hpp>
#include <engine/scene/systems/UI/scene_UI.hpp>
#include <engine/scene/systems/render/render.hpp>
#include <engine/render/render.hpp>

#include <engine/ecs/entities/basic_entity.hpp>

#include <engine/scene/objects/renderable_scene_object.hpp>

#include <engine/scene/objects/camera.hpp>

#include <engine/resource_manager.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/Engine.hpp>

#include <engine/scene/systems/systems_creator.hpp>

#include <engine/scene/components/components.hpp>
#include <engine/scene/components/components_creator.hpp>





using namespace engine::scene::components;
using namespace engine::scene::objects;
using namespace engine::scene::systems;
using namespace engine::input;
using namespace engine::scene;

namespace editor
{
	auto Editor::instance() noexcept -> Editor&
	{
		static Editor instance;
		return instance;
	}



	auto Editor::onStart() noexcept -> void
	{
		AddSystemCreator<camera_update>(1);
		AddSystemCreator<render>(2);
		AddSystemCreator<scene_UI>(3);
		AddSystemCreator<selected_object_UI>(4);

		AddComponentCreator<active_camera>();
		AddComponentCreator<selected>();
		AddComponentCreator<camera_transform>();
		AddComponentCreator<direction>();
		AddComponentCreator<movement>();
		AddComponentCreator<movement_velocity>();
		AddComponentCreator<orientation>();
		AddComponentCreator<position>();
		AddComponentCreator<rotate>();
		AddComponentCreator<rotate_velocity>();
		AddComponentCreator<rotation>();
		AddComponentCreator<scale>();
		AddComponentCreator<transform>();
		AddComponentCreator<velocity>();
		AddComponentCreator<vision>();
		AddComponentCreator<direction_light>();
		AddComponentCreator<light>();
		AddComponentCreator<light_attenuation>();
		AddComponentCreator<point_light>();
		AddComponentCreator<spot_light>();
		AddComponentCreator<color>();
		AddComponentCreator<engine::scene::components::material>();
		AddComponentCreator<mesh>();
		AddComponentCreator<renderable>();



		engine::GetResourceManager().addShadersDirectory("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\shaders");
		engine::GetResourceManager().addModelsDirectory("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\objects");

		auto shader_program = engine::GetResourceManager().loadShaderProgram("Default", "DefaultVS.vs", "DefaultFS.fs");
		auto unlit_shader_program = engine::GetResourceManager().loadShaderProgram("Unlit", "DefaultVS.vs", "UnlitFS.fs");

		std::string path_to_cube = "cube\\Crate\\Crate1.obj";
		std::string path_to_ball = "Ball\\Ball.obj";
		std::string path_to_deer = "deer\\Deer.obj";
		std::string path_to_steve = "Steve\\Model\\Santa\\Steve.obj";
		std::string path_to_backpack = "BackPack\\backpack.obj";

		engine::GetResourceManager().loadModel("Cube", path_to_cube);
		engine::GetResourceManager().loadModel("Steve", path_to_steve);



		Scene::load("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\scenes\\Scene1.scn");



		LOG_INFO("'{0}' application started, size: {1}x{2}", getSettings().getTitle(), getSettings().getWidth(), getSettings().getHeight());
	}



	auto Editor::onKeyboardInput() noexcept -> void
	{
		if (keyboard::isKeyPressed(Key::KEY_ESCAPE))
			close();

		if (keyboard::isKeyPressed(Key::KEY_LEFT_CONTROL) && keyboard::isKeyPressed(Key::KEY_F))
			Scene::save("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\scenes\\Scene1.scn");
	}



	auto Editor::onUpdate() noexcept -> void
	{	
		engine::Engine::getApplicationUIModule()->onUIDrawBegin();
		Scene::update(0.33f);
		engine::Engine::getApplicationUIModule()->onUIDrawEnd();
	}



	auto Editor::onDrawUI() noexcept -> void
	{ }



	auto Editor::onClose() noexcept -> void
	{
		LOG_INFO("'{0}' application closed, size: {1}x{2}", getSettings().getTitle(), getSettings().getWidth(),	getSettings().getHeight());
	}
}