#pragma once

#include <engine/scene/Scene.hpp>

#include <glm/mat4x4.hpp>



namespace engine::scene::components
{
	class transform: public virtual scene_component
	{
	public:

		static constexpr std::string_view component_name = "transform";



		transform() = default;

		glm::mat4 getModelMatrix() const noexcept;
		glm::mat3 getNormalMatrix() const noexcept;

		serialized_view_t serialize() const noexcept override;

	};
}