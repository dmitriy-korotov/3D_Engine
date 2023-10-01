#include <engine/ecs/systems/render_system.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/components/render_component.hpp>
#include <engine/ecs/components/mesh_component.hpp>
#include <engine/ecs/components/transform_component.hpp>
#include <engine/ecs/components/active_camera_component.hpp>
#include <engine/ecs/components/camera_transform_component.hpp>
#include <engine/ecs/components/vision_component.hpp>

#include <engine/render/open_gl/renderer_open_gl.hpp>
#include <engine/render/basic_shader_program.hpp>



namespace engine::ecs::systems
{
	void render_system::update([[maybe_unused]] float _delta_time) const noexcept
	{
		auto components_range = ECS::instance().getComponentsManager()->getComponents<components::render_component>();
		if (components_range.has_value())
		{
			auto& begin = components_range->first;
			auto& end = components_range->second;
			for (;begin != end; begin++)
			{
				auto& component = *begin;
				
				
				const auto& shader_program = component->getShaderProgram();
				const auto& active_camera = ECS::instance().getEntitiesManager()->getEntity(
					ECS::instance().getComponentsManager()->getComponents<components::active_camera_component>()->first->getOwner());
				auto& camera_transform_component = active_camera->getComponent<components::camera_transform_component>()->lock();
				auto& vision_component = active_camera->getComponent<components::vision_component>()->lock();

				auto& owner = ECS::instance().getEntitiesManager()->getEntity(component->getOwner());
				
				
				auto& transform_component = owner->getComponent<components::transform_component>()->lock();
				
				shader_program->setMatrix4f("model_view_matrix", camera_transform_component->getViewMatrix() * transform_component->getModelMatrix());
				shader_program->setMatrix4f("mvp_matrix", vision_component->getProjectionMatrix() * camera_transform_component->getViewMatrix() * transform_component->getModelMatrix());



				auto mesh_component = owner->getComponent<components::mesh_component>();
				if (mesh_component.has_value())
				{
					auto& ptr = mesh_component.value().lock();
					for (const auto& mesh : ptr->getMeshes())
					{
						render::open_gl::renderer::instance().draw(*shader_program, *mesh);
					}
				}

			}
		}
	}
}