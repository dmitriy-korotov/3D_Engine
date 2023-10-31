#include <engine/ecs/components/basic_component.hpp>

#include <engine/logging/log.hpp>

#include <sstream>



namespace engine::ecs::components
{
	size_t basic_component::m_next_component_id = INVALID_COMPONENT_ID;





	basic_component::basic_component() noexcept
		: m_id(generateComponentID())
	{ }



	void basic_component::onConstruct() noexcept
	{ }



	bool basic_component::isActive() const noexcept
	{
		return m_is_active;
	}



	void basic_component::enable() noexcept
	{
		m_is_active = true;
	}



	void basic_component::disable() noexcept
	{
		m_is_active = false;
	}



	entities::entity_id_t basic_component::getOwner() const noexcept
	{
		return m_owner;
	}



	component_id_t basic_component::getID() const noexcept
	{
		return m_id;
	}



	void basic_component::setOwner(entities::entity_id_t _entity_id) noexcept
	{
		m_owner = _entity_id;
	}



	component_id_t basic_component::generateComponentID() noexcept
	{
		return ++m_next_component_id;
	}



	bool basic_component::putOnUI() noexcept
	{
		LOG_WARN("[Basic component WARN] Method 'putOnUI' is not overrided");
		return false;
	}



	json basic_component::dump() const
	{
		json serialize_view;
	
		serialize_view["id"] = m_id;
		serialize_view["is_active"] = m_is_active;
		serialize_view["owner"] = m_owner;

		return serialize_view;
	}



	void basic_component::load(const json& _serialized_view)
	{
		_serialized_view.at("id").get_to(m_id);
		_serialized_view.at("is_active").get_to(m_is_active);
		_serialized_view.at("owner").get_to(m_owner);
}
}