#include <engine/ecs/components/render/light/direction_light.hpp>

#include <engine/Engine.hpp>



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



	bool direction_light::putOnUI() noexcept
	{
		bool is_clicked = false;

		is_clicked |= light::putOnUI();
		is_clicked |= Engine::getApplicationUIModule()->putSliderFloat3("Direction", m_direction, -1.f, 1.f);

		return is_clicked;
	}
}