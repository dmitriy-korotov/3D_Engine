#include <engine/ecs/entities/basic_entity.hpp>

#include <engine/ecs/components/basic_component.hpp>



namespace engine::ecs::entities
{
	entity_id basic_entity::m_next_entity_id = INVALID_ENTITY_ID;
	entity_type_id basic_entity::m_entity_type_id = INVALID_ENTITY_TYPE_ID;



	entity_id basic_entity::generateEntityId() noexcept
	{
		return ++m_next_entity_id;
	}



	void basic_entity::setEntityTypeID(entity_type_id _entity_type_id) noexcept
	{
		m_entity_type_id = _entity_type_id;
	}



	entity_type_id basic_entity::getEntityTypeID() noexcept
	{
		return m_entity_type_id;
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