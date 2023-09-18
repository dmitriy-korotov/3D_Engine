#include <engine/ecs/systems/basic_system.hpp>



namespace engine::ecs::systems
{
	system_type_id basic_system::m_system_type_id = INVALID_SYSTEM_TYPE_ID;



	system_type_id basic_system::getSystemTypeID() noexcept
	{
		return m_system_type_id;
	}



	void basic_system::setSystemTypeID(system_type_id _system_type_id) noexcept
	{
		m_system_type_id = _system_type_id;
	}
}