#pragma once

#include <engine/input/keys.hpp>

#include <cstdint>
#include <functional>



namespace engine::window
{
	enum class Events : uint8_t
	{
		Resize,
		MouseMove,
		Close,

		MouseInput,
		KeyboardInput,

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

	struct KeyboardInputEventData
	{
		input::Key key;
		input::Action action;
	};

	struct MouseInputEventData
	{
		input::MouseButton key;
		input::Action action;
	};





	using ResizeCallBack = std::function<void(const ResizeEventData&)>;
	using MouseMoveCallBack = std::function<void(const MouseMoveEventData&)>;
	using KeyboardInputCallBack = std::function<void(const KeyboardInputEventData&)>;
	using MouseInputCallBack = std::function<void(const MouseInputEventData&)>;
	using CloseCallBack = std::function<void()>;



	struct call_backs_storage
	{
		ResizeCallBack resize_call_back;
		MouseMoveCallBack mouse_move_call_back;
		CloseCallBack close_call_back;
		KeyboardInputCallBack keyboard_input_call_back;
		MouseInputCallBack mouse_input_call_back;
	};
}