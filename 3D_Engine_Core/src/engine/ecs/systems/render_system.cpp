#include <engine/ecs/systems/render_system.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/components/render_component.hpp>
#include <engine/ecs/components/mesh_component.hpp>
#include <engine/ecs/components/transform_component.hpp>

#include <engine/render/open_gl/renderer_open_gl.hpp>
#include <engine/render/basic_shader_program.hpp>



namespace engine::ecs::systems
{
	void render_system::update([[maybe_unused]] float _delta_time) noexcept
	{
		auto components_range = ECS::instance().getComponentsManager()->getComponents<components::render_component>();
		if (components_range.has_value())
		{
			auto& begin = (*components_range).first;
			auto& end = (*components_range).second;
			for (;begin != end; begin++)
			{
				auto& component = *begin;
				
				
				const auto& shader_program = component.second->getShaderProgram();


				auto owner = ECS::instance().getEntitiesManager()->getEntity(component.second->getOwner());
				
				
				auto transform_component = owner->getComponent<components::transform_component>()->lock();
				shader_program->setMatrix4f("model_view_matrix", transform_component->getModelMatrix());



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