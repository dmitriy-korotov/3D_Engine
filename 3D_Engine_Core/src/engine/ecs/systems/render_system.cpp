#include <engine/ecs/systems/render_system.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/components/render_component.hpp>



namespace engine::ecs::systems
{
	void render_system::update([[maybe_unused]] float _delta_time) noexcept
	{
		auto components = ECS::getComponentsManager()->getComponents<components::render_component>();
		if (components.has_value())
		{
			auto& iterator = *components;
			for (;; iterator++)
			{
				
			}
		}
	}
}