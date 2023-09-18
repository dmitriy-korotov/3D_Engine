#pragma once

#include <engine/ecs/components/basic_component.hpp>
#include <engine/render/open_gl/renderer_open_gl.hpp>

#include <memory>



namespace engine::render::open_gl
{
	class shader_program;
}



namespace engine::ecs::components
{
	using render::open_gl::renderer;

	class render_component : public basic_component
	{
	public:

		using shader_program_ptr = std::unique_ptr<render::open_gl::shader_program>;

		render_component(shader_program_ptr _shader_program, renderer::DrawingMode _drawing_mode = renderer::DrawingMode::Triangle) noexcept;

	public:

		shader_program_ptr m_shader_program = nullptr;
		renderer::DrawingMode m_drawing_mode = renderer::DrawingMode::Triangle;

	};
}