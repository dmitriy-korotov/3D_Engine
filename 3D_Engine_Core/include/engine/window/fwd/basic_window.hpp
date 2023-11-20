#pragma once

#include <memory>



namespace engine::window
{
	class basic_window;

	using window_sptr_t = std::shared_ptr<basic_window>;
	using window_wptr_t = std::weak_ptr<basic_window>;
	using window_uptr_t = std::unique_ptr<basic_window>;
}