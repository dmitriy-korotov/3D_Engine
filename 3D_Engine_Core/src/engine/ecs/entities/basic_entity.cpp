#include <engine/ecs/entities/basic_entity.hpp>



namespace engine::ecs::entities
{
	entity_id basic_entity::m_entities_count = 0;



	entity_id basic_entity::generateEntityId() noexcept
	{
		return ++m_entities_count;
	}





	basic_entity::basic_entity()
			: m_id(generateEntityId())
	{ }



	basic_entity::~basic_entity()
	{
		m_id = INVALID_ENTITY_ID;
	}



	entity_id basic_entity::getID() const noexcept
	{
		return m_id;
	}
}