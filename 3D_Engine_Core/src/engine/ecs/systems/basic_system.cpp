#include <engine/ecs/systems/basic_system.hpp>



namespace engine::ecs::systems
{
	auto basic_system::preUpdate(float _delta_time) const noexcept -> void
	{ }

	auto basic_system::postUpdate(float _delta_time) const noexcept -> void
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



	auto basic_system::serialize() const -> serialized_view_t
	{
		serialized_view_t serialized_view;

		serialized_view["is_active"] = m_is_active;

		return serialized_view;
	}



	auto basic_system::deserializeFrom(const serialized_view_t& _dumped_view) -> void
	{ }
}