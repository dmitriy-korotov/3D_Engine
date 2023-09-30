#pragma once

#include <engine/util/noconstructible.hpp>

#include <string>
#include <vector>
#include <stdint.h>



namespace engine::render::open_gl
{
	class vertex_array;

	class renderer: private util::noconstructible
	{
	public:

		enum class Mask : uint8_t
		{
			ColorBuffer,
			DepthBuffer
		};

		enum class DrawingMode : uint8_t
		{
			Point,
			Triangle,
			TriangleStrip,
			Line,
			LineStrip
		};

		static bool init_with_glfw() noexcept;
		static void draw(const vertex_array& _vertex_array_buffer, DrawingMode _drawing_mode = DrawingMode::Triangle) noexcept;
		static void enableDepthTest() noexcept;
		static void disableDepthTest() noexcept;
		static void clear(Mask _mask_type) noexcept;
		static void clear(std::vector<Mask> _mask_types) noexcept;
		static void setClearColor(float _red, float _green, float _blue, float _alpha) noexcept;
		static void setViewport(uint16_t _width, uint16_t _height,
								uint16_t _left_offset = 0, uint16_t _bottom_offset = 0) noexcept;

		static std::string getVendor() noexcept;
		static std::string getRenderer() noexcept;
		static std::string getVersion() noexcept;

	private:

		static void setupDebugContext() noexcept;

	};
}