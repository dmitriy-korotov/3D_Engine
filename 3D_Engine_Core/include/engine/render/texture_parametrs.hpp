#pragma once

#include <stdint.h>



namespace engine::render
{
	enum class InternalFormat : uint8_t
	{
		RGB_8,
		RGB_12,
		RGB_16
	};

	enum class Wrap : uint8_t
	{
		Repeat,
		MirroredRepeat,
		Clamp,
		ClampToEdge,
		ClampToBorder
	};

	enum class Filter : uint8_t
	{
		Linear,
		Nearest,
		NearestMipMapNearest,
		LinearMipMapNearest,
		NearestMipMapLinear,
		LinearMipMapLinear
	};

	struct TextureParamsStorage
	{
		Wrap texture_wrap_s = Wrap::Repeat;
		Wrap texture_wrap_t = Wrap::Repeat;
		Filter texture_min_filter = Filter::Linear;
		Filter texture_mag_filter = Filter::Linear;
	};
}