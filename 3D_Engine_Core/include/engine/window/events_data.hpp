#pragma once

#include <cstdint>
#include <functional>



namespace engine::window
{
	enum class Events : std::uint8_t
	{
		Resize,
		MouseMove,
		Close,

		MouseButtonPress,
		MouseButtonRelease,

		PressKey,
		ReleaseKey
	};



	struct ResizeEventData
	{
		std::uint16_t width;
		std::uint16_t height;
	};

	struct MouseMoveEventData
	{
		double x;
		double y;
	};





	using ResizeCallBack = std::function<void(const ResizeEventData&)>;
	using MouseMoveCallBack = std::function<void(const MouseMoveEventData&)>;



	struct CallBackStorage
	{
		ResizeCallBack resize_call_back_;
		MouseMoveCallBack mouse_move_call_back_;
	};
}