#include <engine/input/mouse.hpp>



namespace engine::input
{
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
}