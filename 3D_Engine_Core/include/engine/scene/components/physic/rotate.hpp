#pragma once

#include <engine/scene/Scene.hpp>



namespace engine::scene::components
{
	class rotate: public scene_component
	{
	public:

		static constexpr std::string_view component_name = "rotate";

		rotate() = default;

		void rotateX(float _delta_angle) const noexcept;
		void rotateY(float _delta_angle) const noexcept;
		void rotateZ(float _delta_angle) const noexcept;

		serialized_view_t serialize() const noexcept override;

	};
}