#include <engine/ecs/systems/systems_manager.hpp>



namespace engine::ecs::systems
{
	void systems_manager::update(float _delta_time)
	{
		for (const auto& system : m_systems)
		{
			if (!system.second.second->isActive())
				continue;

			system.second.second->preUpdate(_delta_time);
			system.second.second->update(_delta_time);
			system.second.second->postUpdate(_delta_time);
		}
	}



	auto systems_manager::getSystems() const noexcept -> const systems_storage_t&
	{
		return m_systems;
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