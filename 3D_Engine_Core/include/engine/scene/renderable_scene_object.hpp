#pragma once

#include <engine/scene/scene_object.hpp>

#include <engine/render/fwd/basic_shader_program.hpp>

#include <string>
#include <memory>



namespace engine::scene
{
	class renderable_scene_object: public scene_object
	{
	public:

		using shader_program_ptr = std::shared_ptr<render::basic_shader_program>;

		renderable_scene_object(std::string_view _model_name,
								std::string_view _program_name) noexcept;

	};
}