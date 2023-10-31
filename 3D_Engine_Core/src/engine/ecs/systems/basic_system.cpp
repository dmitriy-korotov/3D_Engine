#include <engine/ecs/systems/basic_system.hpp>



namespace engine::ecs::systems
{
	void basic_system::preUpdate(float _delta_time) const noexcept
	{ }

	void basic_system::postUpdate(float _delta_time) const noexcept
	{ }



	bool basic_system::isActive() const noexcept
	{
		return m_is_active;
	}



	void basic_system::enable() noexcept
	{
		m_is_active = true;
	}



	void basic_system::disable() noexcept
	{
		m_is_active = false;
	}



	json basic_system::dump() const
	{
		json serialized_view;

		serialized_view["is_active"] = m_is_active;

		return serialized_view;
	}



	void basic_system::load(const json& _dumped_view)
	{ }
}