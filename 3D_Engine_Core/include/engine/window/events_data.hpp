#pragma once

#include <cstdint>


namespace engine
{
	enum class WindowEvents : std::uint8_t
	{
		Resized,
		MouseMoved,
		Closed,

		MouseButtonPress,
		MuseButtonRelease,

		PressKey,
		ReleaseKey
	};



	struct ResizedEventData
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