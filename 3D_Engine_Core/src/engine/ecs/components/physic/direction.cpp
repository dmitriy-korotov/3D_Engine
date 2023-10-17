#include <engine/ecs/components/physic/direction.hpp>

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
}