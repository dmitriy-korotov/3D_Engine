#pragma once

#include <engine/input/keys.hpp>

#include <array>



namespace engine::input
{
	class mouse
	{
	public:

		using keys_storage = std::array<bool, static_cast<size_t>(MouseButton::MOUSE_BUTTON_LAST)>;

		static bool isButtonPressed(MouseButton _mouse_button) noexcept;
		static void pressButton(MouseButton _mouse_button) noexcept;
		static void releaseButton(MouseButton _mouse_button) noexcept;

	private:

		static keys_storage m_mouse_button_keys;

	};
}