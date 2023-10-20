#pragma once

#include <engine/util/noconstructible.hpp>

#include <engine/render/basic_renderer.hpp>

#include <engine/render/open_gl/fwd/vertex_array.hpp>



namespace engine::render::open_gl
{
	class renderer final: public basic_renderer
	{
	public:

		static renderer& instance() noexcept;

		bool init(window::WindowImpl _window_impl) noexcept override;

		void draw(const basic_shader_program& _shader_program, const basic_mesh& _mesh,
				  DrawingMode _drawing_mode = DrawingMode::Triangle) noexcept override;

		void enableDepthTest() noexcept override;
		void disableDepthTest() noexcept override;
		
		void clear(Mask _mask_type) noexcept override;
		void clear(std::vector<Mask> _mask_types) noexcept override;
		
		void setClearColor(float _red, float _green, float _blue, float _alpha) noexcept override;
		void setViewport(uint16_t _width, uint16_t _height,
								uint16_t _left_offset = 0, uint16_t _bottom_offset = 0) noexcept override;

		std::string getVendor() noexcept;
		std::string getRenderer() noexcept;
		std::string getVersion() noexcept;
	
	private:

		renderer() noexcept;

		void setupDebugContext() noexcept;

	};
}