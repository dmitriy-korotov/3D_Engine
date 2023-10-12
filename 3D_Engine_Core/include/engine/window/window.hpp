#pragma once

#include <stdint.h>



namespace engine::window
{
	using window_id_t = size_t;
	constexpr window_id_t INVALID_WINDOW_ID = 0;



	enum class OpenMode : uint8_t
	{
		FullScreen,
		InWindow
	};



	enum class WindowImpl : uint8_t
	{
		GLFW,
		SDL,
		SFML
	};
}