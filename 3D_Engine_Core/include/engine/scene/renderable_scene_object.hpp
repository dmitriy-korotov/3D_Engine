#pragma once

#include <engine/scene/scene_object.hpp>

#include <string>
#include <memory>



namespace engine::render
{
	class basic_shader_program;
}

namespace engine::scene
{
	class renderable_scene_object: public scene_object
	{
	public:

		using shader_program_ptr = std::shared_ptr<render::basic_shader_program>;

		renderable_scene_object(const std::string_view& _path_to_model,
								shader_program_ptr _shader_program = nullptr) noexcept;

	};
}