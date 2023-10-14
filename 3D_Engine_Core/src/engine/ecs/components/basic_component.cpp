#include <engine/ecs/components/basic_component.hpp>

#include <engine/logging/log.hpp>



namespace engine::ecs::components
{
	size_t basic_component::m_next_component_id = INVALID_COMPONENT_ID;





	basic_component::basic_component() noexcept
		: m_id(generateComponentID())
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



	entities::entity_id basic_component::getOwner() const noexcept
	{
		return m_owner;
	}



	component_id basic_component::getID() const noexcept
	{
		return m_id;
	}



	void basic_component::setOwner(entities::entity_id _entity_id) noexcept
	{
		m_owner = _entity_id;
	}



	component_id basic_component::generateComponentID() noexcept
	{
		return ++m_next_component_id;
	}



	void basic_component::putOnUI() noexcept
	{
		LOG_WARN("[Basic component WARN] Method 'putOnUI' is not implemented");
	}
}