#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/window/window.hpp>
#include <engine/window/fwd/basic_window.hpp>

#include <memory>
#include <string>



namespace engine::window
{
	enum class ContextState : uint8_t
	{
		NullState,
		Inited,
		Destroyed
	};

	class basic_window_context: private util::nocopyeble
	{
	public:

		basic_window_context() = default;
		virtual ~basic_window_context() = default;

		[[nodiscard]] virtual std::shared_ptr<basic_window> createWindow() const noexcept = 0;

		virtual void init() const noexcept = 0;
		virtual void terminate() const noexcept = 0;

		ContextState getState() const noexcept;

	protected:

		ContextState m_state = ContextState::NullState;

	};
}