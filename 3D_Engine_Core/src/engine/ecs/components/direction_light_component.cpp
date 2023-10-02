#include <engine/ecs/components/direction_light_component.hpp>



namespace engine::ecs::components
{
	direction_light_component::direction_light_component(const glm::vec3& _direction, const glm::vec3& _ambient,
														 const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept
			: light_component(_ambient, _diffuse, _specular)
			, m_direction(_direction)
	{ }



	void direction_light_component::setDirection(const glm::vec3& _direction) noexcept
	{
		m_direction = _direction;
	}



	const glm::vec3& direction_light_component::getDirection() const noexcept
	{
		return m_direction;
	}
}