#pragma once

#include <cstdint>


namespace engine
{
	enum class EWindowEvents : std::uint8_t
	{
		Resize,
		MouseMove,
		Close,

		PressKey,
		ReleaseKey
	};



	struct ResizeEventData
	{
		std::uint16_t width;
		std::uint16_t height;
	};

	struct MouseMovedEventData
	{
		double x;
		double y;
	};
}