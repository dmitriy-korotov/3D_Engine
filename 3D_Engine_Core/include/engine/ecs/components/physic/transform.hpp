#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/mat4x4.hpp>



namespace engine::ecs::components
{
	class transform: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "transform";



		transform() = default;

		glm::mat4 getModelMatrix() const noexcept;
		glm::mat3 getNormalMatrix() const noexcept;

	};
}