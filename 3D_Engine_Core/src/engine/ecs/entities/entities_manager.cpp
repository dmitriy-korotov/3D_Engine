#include <engine/ecs/entities/entities_manager.hpp>

#include <engine/ecs/entities/basic_entity.hpp>



namespace engine::ecs::entities
{
	void entities_manager::destroyEntity(entity_id _entity_id) noexcept
	{
		m_entities.erase(_entity_id);
	}



	entities_manager::entity_ptr entities_manager::getEntity(entity_id _entity_id) const noexcept
	{
		auto entity = m_entities.find(_entity_id);
		
		if (entity != m_entities.end())
			return (*entity).second;
		else
			return nullptr;
	}



	void entities_manager::destroyAllEntities() noexcept
	{
		m_entities.clear();
	}



	entities_manager::~entities_manager()
	{
		destroyAllEntities();
	}
}