#include <engine/ecs/systems/basic_system.hpp>



namespace engine::ecs::systems
{
	auto basic_system::preUpdate(float _delta_time) noexcept -> void
	{ }

	auto basic_system::postUpdate(float _delta_time) noexcept -> void
	{ }



	auto basic_system::isActive() const noexcept -> bool
	{
		return m_is_active;
	}



	auto basic_system::enable() noexcept -> void
	{
		m_is_active = true;
	}



	auto basic_system::disable() noexcept -> void
	{
		m_is_active = false;
	}
}