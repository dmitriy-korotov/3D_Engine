#include <engine/input/keyboard.hpp>



namespace engine::input
{
	keyboard::keys_storage keyboard::m_keyboard_keys = {};





	auto keyboard::isKeyPressed(Key _key_code) noexcept -> bool
	{
		return m_keyboard_keys[static_cast<size_t>(_key_code)];
	}



	auto keyboard::pressKey(Key _key_code) noexcept -> void
	{
		m_keyboard_keys[static_cast<size_t>(_key_code)] = true;
	}



	auto keyboard::releaseKey(Key _key_code) noexcept -> void
	{
		m_keyboard_keys[static_cast<size_t>(_key_code)] = false;
	}
}