#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/entities/entities_manager.hpp>
#include <engine/ecs/components/components_manager.hpp>



namespace engine::ecs
{
	std::unique_ptr<entities::entities_manager> ECS::m_entities_manager = std::make_unique<entities::entities_manager>();
	std::unique_ptr<components::components_manager> ECS::m_components_manager = std::make_unique<components::components_manager>();





	bool ECS::initialize() noexcept
	{
		return true;
	}



	void ECS::terminate() noexcept
	{
		m_components_manager->removeAllComponents();
		m_entities_manager->destroyAllEntities();
	}



	const ECS::entities_manager_ptr& ECS::getEntitiesManager() noexcept
	{
		return m_entities_manager;
	}



	const ECS::components_manager_ptr& ECS::getComponentsManager() noexcept
	{
		return m_components_manager;
	}



	void ECS::update(float _delta_time) noexcept
	{
		
	}
}