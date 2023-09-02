#pragma once

#include <engine/util/noconstructible.hpp>

#include <string>
#include <stdint.h>



namespace engine::render::open_gl
{
	class vertex_array;

	class renderer : private util::noconstructible
	{
	public:

		enum class Mask : uint8_t
		{
			ColorBuffer,
			DepthBuffer
		};

		enum class DrawingMode : uint8_t
		{
			Triangle,
			Line
		};

		static bool init_with_glfw() noexcept;
		static void draw(const vertex_array& _vertex_array_buffer, DrawingMode _drawing_mode = DrawingMode::Triangle) noexcept;
		static void clear(Mask _mask_type) noexcept;
		static void setClearColor(uint8_t _red, uint8_t _green, uint8_t _blue, float _alpha) noexcept;
		static void setViewport(uint16_t _width, uint16_t _height,
								uint16_t _left_offset = 0, uint16_t _bottom_offset = 0) noexcept;

		static std::string getVendor() noexcept;
		static std::string getRenderer() noexcept;
		static std::string getVersion() noexcept;

	};
}