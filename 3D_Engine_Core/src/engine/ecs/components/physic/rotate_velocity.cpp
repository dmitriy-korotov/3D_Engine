#include <engine/ecs/components/physic/rotate_velocity.hpp>



namespace engine::ecs::components
{
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
}