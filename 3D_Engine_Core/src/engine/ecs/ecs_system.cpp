#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/entities/entities_manager.hpp>
#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/systems/systems_manager.hpp>



namespace engine::ecs
{
	ECS& ECS::instance() noexcept
	{
		static ECS instance;
		return instance;
	}





	ECS::ECS() noexcept
			: m_entities_manager(std::make_unique<entities::entities_manager>())
			, m_components_manager(std::make_unique<components::components_manager>())
			, m_systems_manager(std::make_unique<systems::systems_manager>())
	{ }



	bool ECS::initialize() noexcept
	{
		
		return true;
	}



	void ECS::terminate() noexcept
	{
		m_components_manager->removeAllComponents();
		m_entities_manager->destroyAllEntities();
	}



	const ECS::entities_manager_ptr& ECS::getEntitiesManager() const noexcept
	{
		return m_entities_manager;
	}



	const ECS::components_manager_ptr& ECS::getComponentsManager() const noexcept
	{
		return m_components_manager;
	}



	const ECS::systems_manager_ptr& ECS::getSystemsManager() const noexcept
	{
		return m_systems_manager;
	}



	void ECS::update(float _delta_time) noexcept
	{
		m_systems_manager->update(_delta_time);
	}
}