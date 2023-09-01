#pragma once

#include <string>
#include <stdint.h>



namespace engine::render
{
	class vertex_array;

	class renderer_open_gl
	{
	public:

		renderer_open_gl() = delete;



		static bool init_with_glfw() noexcept;
		static void draw(const vertex_array& _vertex_array_buffer) noexcept;
		static void setClearColor(uint8_t _red, uint8_t _green, uint8_t _blue, float _alpha) noexcept;
		static void setViewport(uint16_t _width, uint16_t _height,
								uint16_t _left_offset = 0, uint16_t _bottom_offset = 0) noexcept;

		static std::string getVendor() noexcept;
		static std::string getRenderer() noexcept;
		static std::string getVersion() noexcept;

	};
}