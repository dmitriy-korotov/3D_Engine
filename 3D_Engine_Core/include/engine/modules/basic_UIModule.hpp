#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/window/common_types.hpp>
#include <engine/render/common_types.hpp>



namespace engine::window
{
	class basic_window;
}

namespace engine::modules
{
	using window::WindowImpl;
	using render::RendererImpl;

	class basic_UIModule: private util::nocopyeble
	{
		using window_ptr = std::shared_ptr<window::basic_window>;

		basic_UIModule() = default;
		virtual ~basic_UIModule() = default;

		void setWindowImpl(WindowImpl _window_impl) noexcept;
		void setRendererImpl(RendererImpl _render_impl) noexcept;
		
		WindowImpl getWindowImpl() const noexcept;
		RendererImpl getRendererImpl() const noexcept;

		virtual void onWindowCreate(const window_ptr& _window_ptr) const noexcept = 0;
		virtual void onWindowShutdown() const noexcept = 0;
		virtual void onUIDrawBegin() noexcept = 0;
		virtual void onUIDrawEnd() noexcept = 0;

		virtual void createDockSpace() const noexcept;

	protected:

		WindowImpl m_window_impl = WindowImpl::GLFW;
		RendererImpl m_render_impl = RendererImpl::OpenGL;

	};
}