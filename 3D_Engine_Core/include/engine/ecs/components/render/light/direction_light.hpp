#pragma once

#include <engine/ecs/components/render/light/light.hpp>



namespace engine::ecs::components
{
	class direction_light: public light
	{
	public:

		static constexpr std::string_view component_name = "direction_light";

		direction_light(const glm::vec3& _direction,
						const glm::vec3& _ambient = glm::vec3(1.f),
						const glm::vec3& _diffuse = glm::vec3(1.f),
						const glm::vec3& _specular = glm::vec3(1.f)) noexcept;

		void setDirection(const glm::vec3& _direction) noexcept;
		const glm::vec3& getDirection() const noexcept;

	private:

		glm::vec3 m_direction;

	};
}