#include <engine/window/basic_window.hpp>

#include <engine/logging/log.hpp>



namespace engine
{
	basic_window::basic_window(const std::string_view& _title)
			: m_window_data_ { 0, 0, _title.data() }
	{ }



	std::uint16_t basic_window::getWidth() const noexcept
	{
		return m_window_data_.width;
	}



	std::uint16_t basic_window::getHeight() const noexcept
	{
		return m_window_data_.height;
	}



	const std::string& basic_window::getTitle() const noexcept
	{
		return m_window_data_.title;
	}
}