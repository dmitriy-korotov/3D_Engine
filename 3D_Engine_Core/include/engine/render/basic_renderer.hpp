#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/window/window.hpp>
#include <engine/render/render.hpp>

#include <string>
#include <vector>



namespace engine::render
{
	class basic_mesh;
}
namespace engine::render
{
	class basic_material;
}



namespace engine::render
{
	using engine::render::basic_mesh;
	using engine::render::basic_material;

	class basic_shader_program;

	class basic_renderer: private util::nocopyeble
	{
	public:

		basic_renderer() = default;
		virtual ~basic_renderer() = default;

		virtual bool init(window::WindowImpl _window_impl) noexcept = 0;
		virtual void draw(const basic_shader_program& _shader_program, const basic_mesh& _mesh,
						  const basic_material& _material, DrawingMode _drawing_mode = DrawingMode::Triangle) noexcept = 0;
		virtual void draw(const basic_shader_program& _shader_program, const basic_mesh& _mesh,
						  DrawingMode _drawing_mode = DrawingMode::Triangle) noexcept = 0;
		virtual void enableDepthTest() noexcept = 0;
		virtual void disableDepthTest() noexcept = 0;
		virtual void clear(Mask _mask_type) noexcept = 0;
		virtual void clear(std::vector<Mask> _mask_types) noexcept = 0;
		virtual void setClearColor(float _red, float _green, float _blue, float _alpha) noexcept = 0;
		virtual void setViewport(uint16_t _width, uint16_t _height,
								 uint16_t _left_offset = 0, uint16_t _bottom_offset = 0) noexcept = 0;

		bool isInited() const noexcept;

	protected:

		bool m_is_inited = false;

	};
}