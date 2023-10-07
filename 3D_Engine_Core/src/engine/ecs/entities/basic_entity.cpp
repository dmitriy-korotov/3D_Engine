#include <engine/ecs/entities/basic_entity.hpp>

#include <engine/ecs/components/basic_component.hpp>



namespace engine::ecs::entities
{
	entity_id basic_entity::m_next_entity_id = INVALID_ENTITY_ID;



	entity_id basic_entity::generateEntityId() noexcept
	{
		return ++m_next_entity_id;
	}





	basic_entity::basic_entity() noexcept
			: m_id(generateEntityId())
	{ }



	entity_id basic_entity::getID() const noexcept
	{
		return m_id;
	}



	basic_entity::~basic_entity()
	{
		m_id = INVALID_ENTITY_ID;
	}
}