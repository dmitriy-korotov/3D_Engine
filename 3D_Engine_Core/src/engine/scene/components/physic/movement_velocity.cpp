#include <engine/scene/components/physic/movement_velocity.hpp>



namespace engine::scene::components
{
	movement_velocity::movement_velocity(const glm::vec3& _movement_velocity) noexcept
			: velocity(_movement_velocity)
	{ }



	auto movement_velocity::setVelocityX(float _x_velocity) noexcept -> void
	{
		m_velocity.x = _x_velocity;
	}



	auto movement_velocity::setVelocityY(float _y_velocity) noexcept -> void
	{
		m_velocity.y = _y_velocity;
	}



	auto movement_velocity::setVelocityZ(float _z_velocity) noexcept -> void
	{
		m_velocity.z = _z_velocity;
	}



	auto movement_velocity::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = velocity::serialize();

		serialized_view["component_name"] = component_name;

		return serialized_view;
	}
}