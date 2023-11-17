#include <editor_app.hpp>

#include <engine/logging/log.hpp>

#include <engine/input/keyboard.hpp>

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/components/physic.hpp>
#include <engine/ecs/components/markers.hpp>
#include <engine/ecs/components/render.hpp>

#include <engine/ecs/systems/physic/camera_update.hpp>
#include <engine/ecs/systems/UI/selected_object_UI.hpp>
#include <engine/ecs/systems/UI/scene_UI.hpp>
#include <engine/ecs/systems/render/render.hpp>
#include <engine/render/render.hpp>

#include <engine/ecs/entities/basic_entity.hpp>

#include <engine/scene/renderable_scene_object.hpp>

#include <engine/scene/objects/camera.hpp>

#include <engine/resource_manager.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/Engine.hpp>

#include <engine/ecs/systems/systems_creator.hpp>

#include <engine/ecs/components/components.hpp>
#include <engine/ecs/components/components_creator.hpp>





using namespace engine::ecs::components;
using namespace engine::ecs::entities;
using namespace engine::ecs::systems;
using namespace engine::input;
using namespace engine::scene;

namespace editor
{
	Editor& Editor::instance() noexcept
	{
		static Editor instance;
		return instance;
	}



	void Editor::onStart() noexcept
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
		AddComponentCreator<engine::ecs::components::material>();
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

		

		/*auto light = Scene::addObject<basic_entity>();
		light->addComponent<direction_light>();


		auto camera = Scene::addObject<engine::scene::camera>(glm::vec3(-5.f, 0.f, 0.f));
		camera->addComponent<active_camera>();

		auto cube = Scene::addObject<renderable_scene_object>("Cube", "Default");
		auto steve = Scene::addObject<renderable_scene_object>("Steve", "Unlit");

		steve->addComponent<point_light>();
		steve->addComponent<selected>();

		steve->addComponent<rotation>();
		steve->addComponent<scale>();*/

		LOG_INFO("'{0}' application started, size: {1}x{2}", getSettings().getTitle(), getSettings().getWidth(), getSettings().getHeight());
	}



	void Editor::onKeyboardInput() noexcept
	{
		if (keyboard::isKeyPressed(Key::KEY_ESCAPE))
			close();

		if (keyboard::isKeyPressed(Key::KEY_LEFT_CONTROL) && keyboard::isKeyPressed(Key::KEY_S))
			Scene::save("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\scenes\\Scene1.scn");
	}



	void Editor::onUpdate() noexcept
	{	
		engine::Engine::getApplicationUIModule()->onUIDrawBegin();
		Scene::update(0.33f);
		engine::Engine::getApplicationUIModule()->onUIDrawEnd();
	}



	void Editor::onDrawUI() noexcept
	{ }



	void Editor::onClose() noexcept
	{
		LOG_INFO("'{0}' application closed, size: {1}x{2}", getSettings().getTitle(), getSettings().getWidth(),	getSettings().getHeight());
	}
}