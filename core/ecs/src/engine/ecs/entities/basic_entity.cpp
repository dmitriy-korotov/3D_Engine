#include <engine/ecs/entities/basic_entity.hpp>

#include <engine/ecs/components/basic_component.hpp>



namespace engine::ecs::entities
{
	entity_id_t basic_entity::m_next_entity_id = INVALID_ENTITY_ID;



	auto basic_entity::generateEntityId() noexcept -> entity_id_t
	{
		return ++m_next_entity_id;
	}





	basic_entity::basic_entity() noexcept
			: m_id(generateEntityId())
	{ }



	auto basic_entity::getID() const noexcept -> entity_id_t
	{
		return m_id;
	}



	basic_entity::~basic_entity()
	{
		m_id = INVALID_ENTITY_ID;
	}
}