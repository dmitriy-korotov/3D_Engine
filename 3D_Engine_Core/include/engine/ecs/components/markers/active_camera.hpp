#pragma once

#include <engine/ecs/components/basic_component.hpp>



namespace engine::ecs::components
{
	class active_camera: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "active_camera";

	};
}