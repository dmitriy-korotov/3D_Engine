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
#include <engine/ecs/systems/UI/UI_scene.hpp>
#include <engine/ecs/systems/render/render.hpp>
#include <engine/render/common_types.hpp>

#include <engine/ecs/entities/basic_entity.hpp>

#include <engine/render/open_gl/shader_program.hpp>
#include <engine/scene/renderable_scene_object.hpp>





using namespace engine::render;
using namespace engine::ecs::components;
using namespace engine::ecs::entities;
using namespace engine::ecs::systems;
using namespace engine::ecs;
using namespace engine::window;
using namespace engine::util;
using namespace engine::modules;

namespace editor
{
	editor_app& editor_app::instance() noexcept
	{
		static editor_app instance;
		return instance;
	}



	void editor_app::onStart() noexcept
	{
		ECS::instance().initialize();



		file_reader vs_reader_2("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\shaders\\DefaultVS.vs");
		file_reader fs_reader_2("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\shaders\\DefaultFS.fs");


		entity_id light = ECS::instance().getEntitiesManager()->createEntity<basic_entity>();
		ECS::instance().getComponentsManager()->addComponent<direction_light>(light);


		entity_id camera = ECS::instance().getEntitiesManager()->createEntity<basic_entity>();

		ECS::instance().getComponentsManager()->addComponent<active_camera>(camera);
		ECS::instance().getComponentsManager()->addComponent<camera_transform>(camera);
		ECS::instance().getComponentsManager()->addComponent<velocity>(camera, glm::vec3(0.05f));
		ECS::instance().getComponentsManager()->addComponent<vision>(camera, Projection::Perspective);

		ECS::instance().getSystemsManager()->addSystem<camera_update>(1);
		ECS::instance().getSystemsManager()->addSystem<render>(2);
		ECS::instance().getSystemsManager()->addSystem<UI_scene>(3);

		auto shader_program = std::make_shared<open_gl::shader_program>(std::move(vs_reader_2.getData()), std::move(fs_reader_2.getData()));

		std::string path = "C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\objects\\cube\\Crate\\Crate1.obj";

		ECS::instance().getEntitiesManager()->createEntity<engine::scene::renderable_scene_object>(path, shader_program);

		LOG_INFO("'{0}' application started, size: {1}x{2}", engine::application_settings::instance().getTitle(),
															 engine::application_settings::instance().getWidth(),
															 engine::application_settings::instance().getHeight());
	}



	void editor_app::onUpdate() noexcept
	{	
		ECS::instance().update(0.33f);
	}



	void editor_app::onDrawUI() noexcept
	{ 
		//UIModule::instance().onUIDrawBegin();

		//UIModule::instance().createDockSpace();
		
		//shader_program_->bind();

		//static int currnet_frame = 0;
		//shader_program_->setInt("current_frame", currnet_frame);
		//m_camera->setProjectionMode(is_perspective_projection ? camera::Projection::Perspective : camera::Projection::Orthographic);
		//shader_program_->setFloat("ambient_factor", ambient_factor);
		//shader_program_->setFloat("diffuse_factor", diffuse_factor);
		//shader_program_->setFloat("specular_factor", specular_factor);
		//shader_program_->setFloat("shiniess", shiniess);
		//shader_program_->setVector3f("source_light_color", glm::vec3(source_light_color[0], source_light_color[1], source_light_color[2]));
		//shader_program_->setVector3f("source_light_position", glm::vec3(translate[0], translate[1], translate[2]));

		//glm::mat4 model_matrix(1);
		//for (const glm::vec3 position : positions)
		//{
		//	glm::mat4 translate_matrix = glm::translate(model_matrix, position);
		//	shader_program_->setMatrix4f("model_view_matrix", m_camera->getViewMatrix() * translate_matrix);
		//	shader_program_->setMatrix4f("mvp_matrix", m_camera->getViewProjectionMatrix() * translate_matrix);
		//	shader_program_->setMatrix3f("normal_matrix", glm::mat3(glm::transpose(glm::inverse(translate_matrix))));
		//	//renderer::instance().draw(*VAO_1buffer_);
		//}

		//glm::mat4 model_matrix_2(1);
		//model_matrix_2 = glm::translate(model_matrix_2, glm::vec3(translate[0], translate[1], translate[2]));
		//model_matrix_2 = glm::scale(model_matrix_2, glm::vec3(scale[0], scale[1], scale[2]));
		//source_light_shader_program_->bind();
		//source_light_shader_program_->setMatrix4f("mvp_matrix", m_camera->getViewProjectionMatrix() * model_matrix_2);
		//source_light_shader_program_->setVector3f("source_light_color", glm::vec3(source_light_color[0], source_light_color[1], source_light_color[2]));
		////renderer::instance().draw(*VAO_1buffer_);

		//ImGui::Begin("BG Color");
		//ImGui::ColorEdit4("Background color", bg_color);
		//ImGui::End();

		//ImGui::Begin("Camera");
		//if (ImGui::SliderFloat3("Camera position", camera_position, -10.f, 10.f))
		//{
		//	m_camera->setPosition(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
		//}
		//if (ImGui::SliderFloat3("Camera rotation", camera_rotation, -360.f, 360.f))
		//{
		//	m_camera->setRotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
		//}
		//ImGui::Separator();
		//ImGui::Checkbox("Perspective projection", &is_perspective_projection);
		//ImGui::Separator();
		//if (ImGui::SliderFloat("Field of view", &field_of_view, 0.f, 180.f))
		//{
		//	m_camera->setFieldOfView(field_of_view);
		//}
		//if (ImGui::SliderFloat("Near plane", &near_plane, 0.1f, 2.f))
		//{
		//	m_camera->setNearPlane(near_plane);
		//}
		//if (ImGui::SliderFloat("Far plane", &far_plane, 2.f, 100.f))
		//{
		//	m_camera->setFarPlane(far_plane);
		//}
		//ImGui::Separator();
		//ImGui::ColorEdit4("Source light color", source_light_color);
		//ImGui::SliderFloat("Ambient factor", &ambient_factor, 0.f, 1.f);
		//ImGui::SliderFloat("Diffuse factor", &diffuse_factor, 0.f, 2.f);
		//ImGui::SliderFloat("Specular factor", &specular_factor, 0.1f, 5.f);
		//ImGui::SliderFloat("Shiniess", &shiniess, 0.1f, 100.f);
		//ImGui::Separator();
		//ImGui::SliderFloat3("Source light position", translate, -10.f, 10.f);
		//ImGui::SliderFloat3("Source light scale", scale, 0.f, 10.f);
		//ImGui::Separator();
		//ImGui::Checkbox("Triangle rendering", &is_triangle_rendering);
		//ImGui::Separator();
		//ImGui::End();

		//UIModule::instance().onUIDrawEnd();
	}



	void editor_app::onClose() noexcept
	{
		LOG_INFO("'{0}' application closed, size: {1}x{2}", engine::application_settings::instance().getTitle(),
															engine::application_settings::instance().getWidth(),
															engine::application_settings::instance().getHeight());
		ECS::instance().terminate();
	}
}