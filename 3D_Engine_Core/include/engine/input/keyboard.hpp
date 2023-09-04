#pragma once

#include <engine/input/keys.hpp>

#include <array>



namespace engine::input
{
	class keyboard
	{
	public:

		using keys_storage = std::array<bool, static_cast<size_t>(KeyCode::KEY_LAST)>;

		static bool isKeyPressed(KeyCode _key_code) noexcept;
		static void pressKey(KeyCode _key_code) noexcept;
		static void releaseKey(KeyCode _key_code) noexcept;

	private:

		static keys_storage s_keys;

	};
}