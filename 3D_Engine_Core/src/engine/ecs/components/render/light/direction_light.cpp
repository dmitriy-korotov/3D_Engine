#include <engine/ecs/components/render/light/direction_light.hpp>

#include <engine/Engine.hpp>



namespace engine::ecs::components
{
	direction_light::direction_light(const glm::vec3& _direction, const glm::vec3& _ambient,
									 const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept
			: light(_ambient, _diffuse, _specular)
			, direction(_direction)
	{ }



	bool direction_light::putOnUI() noexcept
	{
		bool is_clicked = false;

		is_clicked |= light::putOnUI();
		is_clicked |= direction::putOnUI();

		return is_clicked;
	}
}