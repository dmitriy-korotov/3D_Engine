#include <engine/ecs/components/physic/velocity.hpp>



namespace engine::ecs::components
{
	velocity::velocity(const glm::vec3& _velocity = glm::vec3(0.005f)) noexcept
			: m_velocity(_velocity)
	{ }



	void velocity::setVelocity(const glm::vec3& _velocity) noexcept
	{
		m_velocity = _velocity;
	}



	const glm::vec3& velocity::getVelocity() const noexcept
	{
		return m_velocity;
	}
}