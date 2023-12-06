#pragma once

#include <engine/scene/objects/scene_object.hpp>

#include <string>
#include <memory>



namespace engine::scene::objects
{
	class renderable_scene_object: public scene_object
	{
	public:

		renderable_scene_object(std::string_view _model_name,
								std::string_view _program_name) noexcept;

	};
}