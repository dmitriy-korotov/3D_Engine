#include <engine/window/basic_window_context.hpp>



namespace engine::window
{
	ContextState basic_window_context::getState() const noexcept
	{
		return m_state;
	}
}