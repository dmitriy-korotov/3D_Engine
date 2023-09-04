#pragma once

#include <engine/input/keys.hpp>

#include <cstdint>
#include <functional>



namespace engine::window::glfw
{
	enum class Events : uint8_t
	{
		Resize,
		MouseMove,
		Close,

		MouseButtonPress,
		MouseButtonRelease,

		PressKey,
		ReleaseKey,

		Error
	};



	struct ResizeEventData
	{
		uint16_t width;
		uint16_t height;
	};

	struct MouseMoveEventData
	{
		double x;
		double y;
	};

	struct ErrorEventData
	{
		int error_code;
		const char* description;
	};

	struct KeyboardEventData
	{
		input::KeyCode key_code;
		input::Action action;
	};





	using ResizeCallBack = std::function<void(const ResizeEventData&)>;
	using MouseMoveCallBack = std::function<void(const MouseMoveEventData&)>;
	using ErrorCallBack = std::function<void(const ErrorEventData&)>;
	using KeyboardCallBack = std::function<void(const KeyboardEventData&)>;
	using CloseCallBack = std::function<void()>;



	struct CallBackStorage
	{
		ResizeCallBack resize_call_back;
		MouseMoveCallBack mouse_move_call_back;
		ErrorCallBack error_call_back;
		CloseCallBack close_call_back;
		KeyboardCallBack keyboard_call_back;
	};
}