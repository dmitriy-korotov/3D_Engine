#include <engine/window/basic_window.hpp>

#include <engine/logging/log.hpp>



namespace engine
{
	basic_window::basic_window(const std::string_view& _title)
			: m_window_data_ { 0, 0, _title.data() }
	{ }



	uint16_t basic_window::getWidth() const noexcept
	{
		return m_window_data_.width;
	}



	uint16_t basic_window::getHeight() const noexcept
	{
		return m_window_data_.height;
	}



	const std::string& basic_window::getTitle() const noexcept
	{
		return m_window_data_.title;
	}



	const basic_window::bg_color& basic_window::getBackgroundColor() const noexcept
	{
		return m_bg_color_;
	}



	void basic_window::setBackgroundColor(float _red, float _green, float _blue, float _alpha) noexcept
	{
		m_bg_color_[0] = _red;
		m_bg_color_[1] = _green;
		m_bg_color_[2] = _blue;
		m_bg_color_[3] = _alpha;
	}
}