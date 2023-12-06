#pragma once

#include <functional>



namespace engine::window
{
	enum class Events : uint8_t;

	struct ResizeEventData;
	struct MouseMoveEventData;
	struct KeyboardInputEventData;
	struct MouseInputEventData;



	using ResizeCallBack = std::function<void(const ResizeEventData&)>;
	using MouseMoveCallBack = std::function<void(const MouseMoveEventData&)>;
	using KeyboardInputCallBack = std::function<void(const KeyboardInputEventData&)>;
	using MouseInputCallBack = std::function<void(const MouseInputEventData&)>;
	using CloseCallBack = std::function<void()>;



	struct call_backs_storage;;
}