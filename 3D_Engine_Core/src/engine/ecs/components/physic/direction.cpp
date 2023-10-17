#include <engine/ecs/components/physic/direction.hpp>

#include <engine/Engine.hpp>

#include <glm/geometric.hpp>



namespace engine::ecs::components
{
	direction::direction(const glm::vec3& _direction) noexcept
			: m_direction(glm::normalize(_direction))
	{ }



	void direction::setDirection(const glm::vec3& _direction) noexcept
	{
		m_direction = glm::normalize(_direction);
	}



	const glm::vec3& direction::getDirection() const noexcept
	{
		return m_direction;
	}



	bool direction::putOnUI() noexcept
	{
		return Engine::getApplicationUIModule()->putSliderFloat3("Direction", m_direction, -1.f, 1.f);
	}
}