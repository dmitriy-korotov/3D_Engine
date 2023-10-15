#include <engine/ecs/components/render/light/point_light.hpp>



namespace engine::ecs::components
{
	point_light::point_light(const glm::vec3& _position, const glm::vec3& _ambient,
							 const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept
			: light(_ambient, _diffuse, _specular)
			, position(_position)
	{ }



	bool point_light::putOnUI() noexcept
	{
		bool is_clicked = false;

		is_clicked |= position::putOnUI();
		is_clicked |= light::putOnUI();

		return is_clicked;
	}
}