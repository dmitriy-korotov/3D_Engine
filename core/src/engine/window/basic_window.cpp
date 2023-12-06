#include <engine/window/basic_window.hpp>

#include <engine/logging/log.hpp>



namespace engine::window
{
	auto basic_window::setWidth(uint16_t _width) noexcept -> void
	{
		m_width = _width;
	}



	auto basic_window::setHeight(uint16_t _height) noexcept -> void
	{
		m_height = _height;
	}



	auto basic_window::getWidth() const noexcept -> uint16_t
	{
		return m_width;
	}



	auto basic_window::getHeight() const noexcept -> uint16_t
	{
		return m_height;
	}



	auto basic_window::getTitle() const noexcept -> const std::string&
	{
		return m_title;
	}



	auto basic_window::getID() const noexcept -> window_id_t
	{
		return m_id;
	}



	auto basic_window::getCallBacksStorage() const noexcept -> const call_backs_storage&
	{
		return m_window_call_backs;
	}



	auto basic_window::onUpdate() noexcept -> void
	{ }



	auto basic_window::setupIcon(const path& _path_to_icon) const noexcept -> void
	{
		LOG_ERROR("[Basic window ERROR] Method 'setupIcon' is not implemented.");
	}



	auto basic_window::setWindowResizeCallBack() const noexcept -> void
	{
		LOG_ERROR("[Basic window ERROR] Method 'setWindowResizeCallBack' is not implemented.");
	}
	auto basic_window::setWindowCloseCallBack() const noexcept -> void
	{
		LOG_ERROR("[Basic window ERROR] Method 'setWindowCloseCallBack' is not implemented.");
	}
	auto basic_window::setKeyboardInputCallBack() const noexcept -> void
	{
		LOG_ERROR("[Basic window ERROR] Method 'setKeyboardInputCallBack' is not implemented.");
	}
	auto basic_window::setMouseInputCallBack() const noexcept -> void
	{
		LOG_ERROR("[Basic window ERROR] Method 'setMouseInputCallBack' is not implemented.");
	}
	auto basic_window::setMouseMoveCallBack() const noexcept -> void
	{
		LOG_ERROR("[Basic window ERROR] Method 'setMouseMoveCallBack' is not implemented.");
	}
}