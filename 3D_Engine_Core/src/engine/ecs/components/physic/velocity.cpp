#include <engine/ecs/components/physic/velocity.hpp>

#include <engine/Engine.hpp>



namespace engine::ecs::components
{
	velocity::velocity(const glm::vec3& _velocity) noexcept
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



	bool velocity::putOnUI() noexcept
	{
		return Engine::getApplicationUIModule()->putSliderFloat3("Velocity", m_velocity, 0.f, 1.f);
	}
}