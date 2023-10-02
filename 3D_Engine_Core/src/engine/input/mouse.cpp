#include <engine/input/mouse.hpp>



namespace engine::input
{
	double mouse::m_cursor_position_x = 0;
	double mouse::m_cursor_position_y = 0;
	mouse::keys_storage mouse::m_mouse_button_keys = {};





	bool mouse::isButtonPressed(MouseButton _mouse_button) noexcept
	{
		return m_mouse_button_keys[static_cast<size_t>(_mouse_button)];
	}



	void mouse::pressButton(MouseButton _mouse_button) noexcept
	{
		m_mouse_button_keys[static_cast<size_t>(_mouse_button)] = true;
	}



	void mouse::releaseButton(MouseButton _mouse_button) noexcept
	{
		m_mouse_button_keys[static_cast<size_t>(_mouse_button)] = false;
	}



	void mouse::setCursorPosition(double _x, double _y) noexcept
	{
		m_cursor_position_x = _x;
		m_cursor_position_y = _y;
	}



	double mouse::getCursorPositionX() noexcept
	{
		return m_cursor_position_x;
	}



	double mouse::getCursorPositionY() noexcept
	{
		return m_cursor_position_y;
	}
}