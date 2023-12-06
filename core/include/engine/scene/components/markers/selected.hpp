#pragma once

#include <engine/scene/Scene.hpp>



namespace engine::scene::components
{
	class selected: public virtual scene_component
	{
	public:

		static constexpr std::string_view component_name = "selected";

		serialized_view_t serialize() const noexcept override;

	};
}