#include <engine/ecs/components/physic/rotate_velocity.hpp>



namespace engine::ecs::components
{
	rotate_velocity::rotate_velocity(const glm::vec3& _rotate_velocity) noexcept
			: velocity(_rotate_velocity)
	{ }



	void rotate_velocity::setVelocityRoll(float _roll_velocity) noexcept
	{
		m_velocity.x = _roll_velocity;
	}



	void rotate_velocity::setVelocityPitch(float _pitch_velocity) noexcept
	{
		m_velocity.y = _pitch_velocity;
	}



	void rotate_velocity::setVelocityYaw(float _yaw_velocity) noexcept
	{
		m_velocity.z = _yaw_velocity;
	}



	auto rotate_velocity::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = velocity::serialize();

		serialized_view["component_name"] = component_name;

		return serialized_view;
	}
}