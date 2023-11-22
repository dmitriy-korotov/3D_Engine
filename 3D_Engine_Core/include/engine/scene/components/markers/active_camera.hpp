#pragma once

#include <engine/scene/Scene.hpp>



namespace engine::scene::components
{
	class active_camera: public virtual scene_component
	{
	public:

		static constexpr std::string_view component_name = "active_camera";

		serialized_view_t serialize() const noexcept override;

	};
}