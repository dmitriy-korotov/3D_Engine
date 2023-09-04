#include <engine/input/keyboard.hpp>



namespace engine::input
{
	keyboard::keys_storage keyboard::s_keys = {};





	bool keyboard::isKeyPressed(KeyCode _key_code) noexcept
	{
		return s_keys[static_cast<size_t>(_key_code)];
	}



	void keyboard::pressKey(KeyCode _key_code) noexcept
	{
		s_keys[static_cast<size_t>(_key_code)] = true;
	}



	void keyboard::releaseKey(KeyCode _key_code) noexcept
	{
		s_keys[static_cast<size_t>(_key_code)] = false;
	}
}