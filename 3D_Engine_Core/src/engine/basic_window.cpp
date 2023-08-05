#include <engine/window/basic_window.hpp>

#include <engine/logging/log.hpp>



namespace engine
{
	basic_window::basic_window(std::uint16_t _width, std::uint16_t _height,
							   const std::string_view& _title)
			: m_width(_width)
			, m_height(_height)
			, m_title(_title)
	{ }



	std::uint16_t basic_window::getWidth() const noexcept
	{
		return m_width;
	}



	std::uint16_t basic_window::getHeight() const noexcept
	{
		return m_height;
	}



	const std::string& basic_window::getTitle() const noexcept
	{
		return m_title;
	}
}