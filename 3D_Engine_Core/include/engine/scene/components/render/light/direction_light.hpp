#pragma once

#include <engine/scene/components/render/light/light.hpp>
#include <engine/scene/components/physic/direction.hpp>



namespace engine::scene::components
{
	class direction_light: public light,
						   public direction
	{
	public:

		static constexpr std::string_view component_name = "direction_light";



		direction_light(const glm::vec3& _direction = glm::vec3(0.f, 0.f, -1.f),
						const glm::vec3& _ambient = glm::vec3(0.1f),
						const glm::vec3& _diffuse = glm::vec3(1.f),
						const glm::vec3& _specular = glm::vec3(5.f)) noexcept;

		bool putOnUI() noexcept override;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	};
}