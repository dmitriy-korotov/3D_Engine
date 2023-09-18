#include <engine/ecs/components/basic_component.hpp>



namespace engine::ecs::components
{
	component_type_id basic_component::m_component_type_id = INVALID_COMPONENT_TYPE_ID;

	size_t basic_component::m_next_component_id = INVALID_COMPONENT_ID;





	basic_component::basic_component() noexcept
		: m_id(generateComponentID())
	{ }



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



	void basic_component::setComponentTypeID(component_type_id _component_type_id) noexcept
	{
		m_component_type_id = _component_type_id;
	}



	component_type_id basic_component::getComponentTypeID() noexcept
	{
		return m_component_type_id;
	}



	component_id basic_component::generateComponentID() noexcept
	{
		return ++m_next_component_id;
	}
}