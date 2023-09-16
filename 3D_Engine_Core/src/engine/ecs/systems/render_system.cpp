#include <engine/ecs/systems/render_system.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/components/render_component.hpp>

#include <engine/render/open_gl/renderer_open_gl.hpp>
#include <engine/render/open_gl/shader_program.hpp>



namespace engine::ecs::systems
{
	void render_system::update([[maybe_unused]] float _delta_time) noexcept
	{
		auto components_range = ECS::getComponentsManager()->getComponents<components::render_component>();
		if (components_range.has_value())
		{
			auto& begin = (*components_range).first;
			auto& end = (*components_range).second;
			for (;begin != end; begin++)
			{
				auto& component = *begin;
				//ECS::getComponentsManager()->getComponent(component->getOwner());
				//component->m_shader_program->bind();
				//render::open_gl::renderer::draw();
			}
		}
	}
}