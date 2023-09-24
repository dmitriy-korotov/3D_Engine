#include <engine/window/basic_window.hpp>

#include <engine/logging/log.hpp>



namespace engine::window
{
	void basic_window::setWidth(uint16_t _width) noexcept
	{
		m_width = _width;
	}



	void basic_window::setHeight(uint16_t _height) noexcept
	{
		m_height = _height;
	}



	uint16_t basic_window::getWidth() const noexcept
	{
		return m_width;
	}



	uint16_t basic_window::getHeight() const noexcept
	{
		return m_height;
	}



	const std::string& basic_window::getTitle() const noexcept
	{
		return m_title;
	}



	window_id_t basic_window::getID() const noexcept
	{
		return m_id;
	}



	const call_backs_storage& basic_window::getCallBacksStorage() const noexcept
	{
		return m_window_call_backs;
	}



	void basic_window::onUpdate() noexcept
	{ }



	void basic_window::setWindowResizeCallBack() const noexcept {}
	void basic_window::setWindowCloseCallBack() const noexcept {}
	void basic_window::setKeyboardInputCallBack() const noexcept {}
	void basic_window::setMouseInputCallBack() const noexcept {}
}