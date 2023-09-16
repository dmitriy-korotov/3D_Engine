#include <engine/ecs/systems/systems_manager.hpp>

#include <engine/ecs/systems/basic_system.hpp>



namespace engine::ecs::systems
{
	void systems_manager::update(float _delta_time)
	{
		for (auto& system : m_systems)
		{
			system->update(_delta_time);
		}
	}
}