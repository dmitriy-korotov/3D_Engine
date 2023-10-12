#pragma once

#include <engine/window/windows_collector.hpp>



namespace engine::window
{
	class windows_manager final: public windows_collector
	{
	public:

		static windows_manager& instance() noexcept;

		[[nodiscard]] window_ptr getWindow(window_id_t _window_id) const noexcept;

	private:

		windows_manager() = default;

	};
}