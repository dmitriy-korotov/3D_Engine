#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/mat4x4.hpp>



namespace engine::ecs::components
{
	class camera_transform: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "camera_transform";



		glm::mat4 getViewMatrix() const noexcept;

		serialized_view_t serialize() const noexcept override;

	};
}