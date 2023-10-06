#include <engine/ecs/systems/render/render.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/render.hpp>
#include <engine/ecs/components/physic.hpp>
#include <engine/ecs/components/markers.hpp>

#include <engine/render/open_gl/renderer_open_gl.hpp>
#include <engine/render/basic_shader_program.hpp>



using namespace engine::render::open_gl;
using namespace engine::ecs::components;



namespace engine::ecs::systems
{
	void render::update([[maybe_unused]] float _delta_time) const noexcept
	{
		auto renderable_components = ECS::instance().getComponentsManager()->getComponents<components::renderable>();
		if (renderable_components.has_value())
		{
			auto& [begin, end] = renderable_components.value();

			for (;begin != end; begin++)
			{
				auto& renderable_comp = *begin;
				
				

				const auto& shader_program = renderable_comp->getShaderProgram();
				
				

				const auto& active_camera_comp = *ECS::instance().getComponentsManager()->getComponents<active_camera>()->first;
				const auto& active_camera_ent = ECS::instance().getEntitiesManager()->getEntity(active_camera_comp->getOwner());
				auto& camera_transform_comp = active_camera_ent->getComponent<camera_transform>()->lock();
				auto& vision_comp = active_camera_ent->getComponent<vision>()->lock();



				auto& current_ent = ECS::instance().getEntitiesManager()->getEntity(renderable_comp->getOwner());
				

				
				auto& transform_comp = current_ent->getComponent<transform>()->lock();



				shader_program->bind();
				shader_program->setMatrix4f("model_view_matrix", camera_transform_comp->getViewMatrix() * transform_comp->getModelMatrix());
				glm::mat4 mvp_matrix = vision_comp->getProjectionMatrix() * camera_transform_comp->getViewMatrix() * transform_comp->getModelMatrix();
				shader_program->setMatrix4f("mvp_matrix", mvp_matrix);
				shader_program->setMatrix3f("normal_matrix", transform_comp->getNormalMatrix());



				const auto& direction_light_comp = *ECS::instance().getComponentsManager()->getComponents<direction_light>()->first;



				//shader_program->setVector3f
				shader_program->setVector3f("light.direction", direction_light_comp->getDirection());
				shader_program->setVector3f("light.ambient", direction_light_comp->getAmbient());
				shader_program->setVector3f("light.diffuse", direction_light_comp->getDiffuse());
				shader_program->setVector3f("light.specular", direction_light_comp->getSpecular());



				auto mesh_comp = current_ent->getComponent<mesh>();
				auto material_comp = current_ent->getComponent<material>().value().lock();
				if (mesh_comp.has_value())
				{

					for (const auto& mesh : mesh_comp->lock()->getMeshes())
					{
						renderer::instance().draw(*shader_program, *mesh, *material_comp->getMaterial());
					}
				}
			}
		}
	}
}