#include <engine/window/basic_window_context.hpp>



namespace engine::window
{
	auto basic_window_context::getState() const noexcept -> ContextState
	{
		return m_state;
	}
}