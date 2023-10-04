#pragma once

#include <engine/ecs/components/render/light/light_component.hpp>



namespace engine::ecs::components
{
	class direction_light_component: public light_component
	{
	public:

		static constexpr std::string_view component_name = "direction_light_component";

		direction_light_component(const glm::vec3& _direction,
								  const glm::vec3& _ambient = glm::vec3(1.f),
								  const glm::vec3& _diffuse = glm::vec3(1.f),
								  const glm::vec3& _specular = glm::vec3(1.f)) noexcept;

		void setDirection(const glm::vec3& _direction) noexcept;
		const glm::vec3& getDirection() const noexcept;

	private:

		glm::vec3 m_direction;

	};
}