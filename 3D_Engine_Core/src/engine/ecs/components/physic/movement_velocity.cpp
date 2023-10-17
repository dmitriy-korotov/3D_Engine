#include <engine/ecs/components/physic/movement_velocity.hpp>



namespace engine::ecs::components
{
	movement_velocity::movement_velocity(const glm::vec3& _movement_velocity) noexcept
			: velocity(_movement_velocity)
	{ }



	void movement_velocity::setVelocityX(float _x_velocity) noexcept
	{
		m_velocity.x = _x_velocity;
	}



	void movement_velocity::setVelocityY(float _y_velocity) noexcept
	{
		m_velocity.y = _y_velocity;
	}



	void movement_velocity::setVelocityZ(float _z_velocity) noexcept
	{
		m_velocity.z = _z_velocity;
	}
}