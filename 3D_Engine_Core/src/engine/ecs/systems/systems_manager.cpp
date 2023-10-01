#include <engine/ecs/systems/systems_manager.hpp>

#include <engine/ecs/systems/basic_system.hpp>



namespace engine::ecs::systems
{
	void systems_manager::update(float _delta_time)
	{
		for (const auto& system : m_systems)
		{
			system.second->update(_delta_time);
		}
	}



	void systems_manager::removeAllSystems() noexcept
	{
		m_systems.clear();
	}



	systems_manager::~systems_manager()
	{
		removeAllSystems();
	}
}