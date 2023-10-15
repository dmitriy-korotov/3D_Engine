#pragma once

#include <engine/ecs/components/render/light/light.hpp>

#include <engine/ecs/components/physic/position.hpp>



namespace engine::ecs::components
{
	class point_light: public light,
					   public position
	{
	public:

		static constexpr std::string_view component_name = "point_light";



		point_light(const glm::vec3& _position = glm::vec3(0.f),
					const glm::vec3& _ambient = glm::vec3(0.1f),
					const glm::vec3& _diffuse = glm::vec3(1.f),
					const glm::vec3& _specular = glm::vec3(0.5f)) noexcept;

		bool putOnUI() noexcept override;

	};
}