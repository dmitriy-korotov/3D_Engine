#pragma once

#include <engine/scene/Scene.hpp>

#include <glm/mat4x4.hpp>



namespace engine::scene::components
{
	class camera_transform: public virtual scene_component
	{
	public:

		static constexpr std::string_view component_name = "camera_transform";



		glm::mat4 getViewMatrix() const noexcept;

		serialized_view_t serialize() const noexcept override;

	};
}