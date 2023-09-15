#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/entities/entities_manager.hpp>
#include <engine/ecs/components/components_manager.hpp>



namespace engine::ecs
{
	bool ECS::initialize() noexcept
	{
		return true;
	}



	void ECS::terminate() noexcept
	{
		m_components_manager->removeAllComponents();
		m_entities_manager->destroyAllEntities();
	}
}