#include <editor_app.hpp>

#include <engine/logging/log.hpp>

#include <engine/application_settings.hpp>

#include <engine/input/keyboard.hpp>

#include <engine/util/file_reader.hpp>

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





using namespace engine::render;
using namespace engine::ecs::components;
using namespace engine::ecs::entities;
using namespace engine::ecs::systems;
using namespace engine::ecs;
using namespace engine::window;
using namespace engine::util;
using namespace engine::modules;
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
		engine::GetResourceManager().addShadersDirectory("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\shaders");


		entity_id_t light = Scene::addObject<basic_entity>(nullptr);
		Scene::addComponent<direction_light>(light);


		entity_id_t camera_id = Scene::addObject<camera>(nullptr, glm::vec3(-5.f, 0.f, 0.f));
		Scene::addComponent<active_camera>(camera_id);



		Scene::addSystem<camera_update>(1);
		Scene::addSystem<render>(2);
		Scene::addSystem<selected_object_UI>(5);
		Scene::addSystem<scene_UI>(4);

		

		auto shader_program = engine::GetResourceManager().loadShaderProgram("Default", "DefaultVS.vs", "DefaultFS.fs");
		auto unlit_shader_program = engine::GetResourceManager().loadShaderProgram("Unlit", "DefaultVS.vs", "UnlitFS.fs");
		
		std::string path_to_cube = "C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\objects\\cube\\Crate\\Crate1.obj";
		std::string path_to_ball = "C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\objects\\Ball\\Ball.obj";
		//std::string path = "C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\objects\\MyCube\\Cube.obj";
		//std::string path = "C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\objects\\E-45-Aircraft\\E_45_Aircraft_obj.obj";
		//std::string path = "C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\objects\\BackPack\\backpack.obj";

		entity_id_t ball = Scene::addObject<renderable_scene_object>(nullptr, path_to_cube, shader_program);
		entity_id_t cube = Scene::addObject<renderable_scene_object>(nullptr, path_to_cube, unlit_shader_program);

		Scene::addComponent<point_light>(cube);
		Scene::addComponent<selected>(cube);







		LOG_INFO("'{0}' application started, size: {1}x{2}", engine::application_settings::instance().getTitle(),
															 engine::application_settings::instance().getWidth(),
															 engine::application_settings::instance().getHeight());
	}



	void Editor::onKeyboardInput() noexcept
	{
		if (keyboard::isKeyPressed(Key::KEY_ESCAPE))
			close();
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
		LOG_INFO("'{0}' application closed, size: {1}x{2}", engine::application_settings::instance().getTitle(),
															engine::application_settings::instance().getWidth(),
															engine::application_settings::instance().getHeight());
	}
}