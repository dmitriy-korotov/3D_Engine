#include <engine/ecs/components/render/light/direction_light.hpp>



namespace engine::ecs::components
{
	direction_light::direction_light(const glm::vec4& _color, const glm::vec3& _direction, const glm::vec3& _ambient,
									 const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept
			: light(_color, _ambient, _diffuse, _specular)
			, m_direction(_direction)
	{ }



	void direction_light::setDirection(const glm::vec3& _direction) noexcept
	{
		m_direction = _direction;
	}



	const glm::vec3& direction_light::getDirection() const noexcept
	{
		return m_direction;
	}
}