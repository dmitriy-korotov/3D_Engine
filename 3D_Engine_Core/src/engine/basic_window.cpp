#include <engine/basic_window.hpp>



namespace engine
{
	basic_window::basic_window(std::uint16_t _width, std::uint16_t _height,
		const std::string_view& _title)
		: m_width(_width)
		, m_height(_height)
		, m_title(_title)
	{
		init();
	}



	basic_window::~basic_window()
	{
		shutdown();
	}
}