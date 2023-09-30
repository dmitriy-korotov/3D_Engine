#pragma once

#include <stdint.h>



namespace engine::render
{
	enum class RendererImpl : uint8_t
	{
		OpenGL,
		Vulkan,
		DirectX,
		Direct3D
	};



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
}