#include <engine/ecs/components/basic_component.hpp>



namespace engine::ecs::components
{
	component_type_id basic_component::s_component_type_id = INVALID_COMPONENT_TYPE_ID;

	size_t basic_component::m_components_count = 0;





	basic_component::basic_component() noexcept
		: m_id(generateComponentID())
	{ }



	void basic_component::setOwner(entities::entity_id _entity_id) noexcept
	{
		m_owner = _entity_id;
	}



	void basic_component::setComponentTypeID(component_type_id _component_type_id) noexcept
	{
		s_component_type_id = _component_type_id;
	}



	component_type_id basic_component::getComponentTypeID() noexcept
	{
		return s_component_type_id;
	}



	component_id basic_component::generateComponentID() noexcept
	{
		return ++m_components_count;
	}
}