#include <engine/window/basic_window.hpp>

#include <engine/logging/log.hpp>



namespace engine
{
	basic_window::basic_window(std::uint16_t _width, std::uint16_t _height,
							   const std::string_view& _title)
			: m_window_data { _width, _height, _title.data() }
	{ }



	std::uint16_t basic_window::getWidth() const noexcept
	{
		return m_window_data.width;
	}



	std::uint16_t basic_window::getHeight() const noexcept
	{
		return m_window_data.height;
	}



	const std::string& basic_window::getTitle() const noexcept
	{
		return m_window_data.title;
	}
}