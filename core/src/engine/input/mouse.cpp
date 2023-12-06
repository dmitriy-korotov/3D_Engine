#include <engine/input/mouse.hpp>



namespace engine::input
{
	double mouse::m_cursor_position_x = 0;
	double mouse::m_cursor_position_y = 0;
	mouse::keys_storage mouse::m_mouse_button_keys = {};





	auto mouse::isButtonPressed(MouseButton _mouse_button) noexcept -> bool
	{
		return m_mouse_button_keys[static_cast<size_t>(_mouse_button)];
	}



	auto mouse::pressButton(MouseButton _mouse_button) noexcept -> void
	{
		m_mouse_button_keys[static_cast<size_t>(_mouse_button)] = true;
	}



	auto mouse::releaseButton(MouseButton _mouse_button) noexcept -> void
	{
		m_mouse_button_keys[static_cast<size_t>(_mouse_button)] = false;
	}



	auto mouse::setCursorPosition(double _x, double _y) noexcept -> void
	{
		m_cursor_position_x = _x;
		m_cursor_position_y = _y;
	}



	auto mouse::getCursorPositionX() noexcept -> double
	{
		return m_cursor_position_x;
	}



	auto mouse::getCursorPositionY() noexcept -> double
	{
		return m_cursor_position_y;
	}
}