#include <engine/ecs/entities/entities_manager.hpp>

#include <engine/ecs/entities/basic_entity.hpp>



namespace engine::ecs::entities
{
	void entities_manager::destroyEntity(entity_id _entity_id) noexcept
	{
		auto removed_element_iter = std::remove_if(m_entities.begin(), m_entities.end(),
												   [&_entity_id](const auto& _entity_ptr) -> bool
												   {
														return _entity_ptr->m_id == _entity_id;
												   });
		m_entities.erase(removed_element_iter);
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