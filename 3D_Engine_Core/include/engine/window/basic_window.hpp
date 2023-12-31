#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/error/window_error.hpp>

#include <engine/window/window.hpp>
#include <engine/window/events.hpp>

#include <glm/vec2.hpp>

#include <string>
#include <filesystem>
#include <optional>
#include <memory>



namespace engine::window
{
	using std::filesystem::path;

	class basic_window: private util::nocopyeble
	{
	public:

		using window_err_t = std::optional<error::window_error>;
		


		basic_window() = default;
		virtual ~basic_window() = default;

		void setWidth(uint16_t _width) noexcept;
		void setHeight(uint16_t _height) noexcept;

		uint16_t getWidth() const noexcept;
		uint16_t getHeight() const noexcept;
		const std::string& getTitle() const noexcept;
		window_id_t getID() const noexcept;

		const call_backs_storage& getCallBacksStorage() const noexcept;

		virtual window_err_t create(const std::string_view& _title, uint16_t _width,
								  uint16_t _height, OpenMode _open_mode = OpenMode::InWindow) noexcept = 0;

		virtual void shutdown() noexcept = 0;
		virtual void onUpdate() noexcept;

		virtual glm::dvec2 getCurrentCursorPosition() const noexcept = 0;
		virtual void setupIcon(const path& _path_to_icon) const noexcept;

		template<Events _event_type, typename CallBackFunction>
		void addEventListener(CallBackFunction _call_back) noexcept;

	protected:

		virtual void setWindowResizeCallBack() const noexcept;
		virtual void setWindowCloseCallBack() const noexcept;
		virtual void setKeyboardInputCallBack() const noexcept;
		virtual void setMouseInputCallBack() const noexcept;
		virtual void setMouseMoveCallBack() const noexcept;

	protected:

		window_id_t m_id = INVALID_WINDOW_ID;

		uint16_t m_width = 0;
		uint16_t m_height = 0;
		std::string m_title;

		call_backs_storage m_window_call_backs;
	};





	using window_sptr_t = std::shared_ptr<basic_window>;
	using window_wptr_t = std::weak_ptr<basic_window>;
	using window_uptr_t = std::unique_ptr<basic_window>;





	template<Events _event_type, typename CallBackFunction>
	void basic_window::addEventListener(CallBackFunction _call_back) noexcept
	{
		if constexpr (_event_type == Events::Resize)
		{
			m_window_call_backs.resize_call_back = std::move(_call_back);
			setWindowResizeCallBack();
		}
		if constexpr (_event_type == Events::Close)
		{
			m_window_call_backs.close_call_back = std::move(_call_back);
			setWindowCloseCallBack();
		}
		if constexpr (_event_type == Events::KeyboardInput)
		{
			m_window_call_backs.keyboard_input_call_back = std::move(_call_back);
			setKeyboardInputCallBack();
		}
		if constexpr (_event_type == Events::MouseInput)
		{
			m_window_call_backs.mouse_input_call_back = std::move(_call_back);
			setMouseInputCallBack();
		}
		if constexpr (_event_type == Events::MouseMove)
		{
			m_window_call_backs.mouse_move_call_back = std::move(_call_back);
			setMouseMoveCallBack();
		}
	}
}