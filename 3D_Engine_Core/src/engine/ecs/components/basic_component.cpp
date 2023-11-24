#include <engine/ecs/components/basic_component.hpp>

#include <engine/logging/log.hpp>

#include <sstream>



namespace engine::ecs::components
{
	size_t basic_component::m_next_component_id = INVALID_COMPONENT_ID;





	basic_component::basic_component() noexcept
		: m_id(generateComponentID())
	{ }



	auto basic_component::setID(component_id_t _id) noexcept -> void
	{
		m_id = _id;
	}



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
}