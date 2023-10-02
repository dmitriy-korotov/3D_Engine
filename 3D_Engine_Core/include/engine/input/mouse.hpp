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
		static void setCursorPosition(double _x, double _y) noexcept;
		static double getCursorPositionX() noexcept;
		static double getCursorPositionY() noexcept;

	private:

		static double m_cursor_position_x;
		static double m_cursor_position_y;
		static keys_storage m_mouse_button_keys;

	};
}