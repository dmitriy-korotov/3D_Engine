#include <engine/ecs/components/basic_component.hpp>

#include <engine/logging/log.hpp>

#include <sstream>



namespace engine::ecs::components
{
	size_t basic_component::m_next_component_id = INVALID_COMPONENT_ID;





	basic_component::basic_component() noexcept
		: m_id(generateComponentID())
	{ }



	auto basic_component::onConstruct() noexcept -> void
	{ }



	auto basic_component::isActive() const noexcept -> bool
	{
		return m_is_active;
	}



	auto basic_component::enable() noexcept -> void
	{
		m_is_active = true;
	}



	auto basic_component::disable() noexcept -> void
	{
		m_is_active = false;
	}



	auto basic_component::getOwner() const noexcept -> entities::entity_id_t
	{
		return m_owner;
	}



	auto basic_component::getID() const noexcept -> component_id_t
	{
		return m_id;
	}



	auto basic_component::setOwner(entities::entity_id_t _entity_id) noexcept -> void
	{
		m_owner = _entity_id;
	}



	auto basic_component::generateComponentID() noexcept -> component_id_t
	{
		return ++m_next_component_id;
	}



	auto basic_component::putOnUI() noexcept -> bool
	{
		LOG_WARN("[Basic component WARN] Method 'putOnUI' is not overrided");
		return false;
	}



	auto basic_component::serialize() const -> serialized_view_t
	{
		serialized_view_t serialize_view;
	
		serialize_view["id"] = m_id;
		serialize_view["is_active"] = m_is_active;
		serialize_view["owner"] = m_owner;

		return serialize_view;
	}



	auto basic_component::deserializeFrom(const serialized_view_t& _serialized_view) -> void
	{
		_serialized_view.at("id").get_to(m_id);
		_serialized_view.at("is_active").get_to(m_is_active);
		_serialized_view.at("owner").get_to(m_owner);
	}
}