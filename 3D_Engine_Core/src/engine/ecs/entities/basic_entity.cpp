#include <engine/ecs/entities/basic_entity.hpp>

#include <engine/ecs/components/basic_component.hpp>



namespace engine::ecs::entities
{
	entity_id_t basic_entity::m_next_entity_id = INVALID_ENTITY_ID;



	entity_id_t basic_entity::generateEntityId() noexcept
	{
		return ++m_next_entity_id;
	}





	basic_entity::basic_entity() noexcept
			: m_id(generateEntityId())
	{ }



	entity_id_t basic_entity::getID() const noexcept
	{
		return m_id;
	}



	json basic_entity::dump() const
	{
		json serialize_view;

		serialize_view["id"] = m_id;

		return serialize_view;
	}



	void basic_entity::load(const json& _serialized_view)
	{
		_serialized_view.at("id").get_to(m_id);
	}



	basic_entity::~basic_entity()
	{
		m_id = INVALID_ENTITY_ID;
	}
}