#pragma once

#include <engine/window/window.hpp>
#include <engine/render/render.hpp>
#include <engine/modules/ui/ui.hpp>

#include <engine/modules/ui/basic_UICreator.hpp>

#include <engine/window/fwd/basic_window.hpp>

#include <memory>



namespace engine::modules::ui
{
	using window::WindowImpl;
	using render::RendererImpl;

	class basic_UIModule: public basic_UICreator
	{
	public:

		using window_ptr = std::shared_ptr<window::basic_window>;



		void setWindowImpl(WindowImpl _window_impl) noexcept;
		void setRendererImpl(RendererImpl _render_impl) noexcept;
		bool isInitialized() const noexcept;
		
		WindowImpl getWindowImpl() const noexcept;
		RendererImpl getRendererImpl() const noexcept;



		virtual void initialize(const window_ptr& _window_ptr) noexcept = 0;
		virtual void terminate() noexcept = 0;

		virtual void onUIDrawBegin() const noexcept = 0;
		virtual void onUIDrawEnd() const noexcept = 0;

		virtual bool isMouseOnUI() const noexcept = 0;

	protected:

		bool m_is_inited = false;

		WindowImpl m_window_impl = WindowImpl::GLFW;
		RendererImpl m_render_impl = RendererImpl::OpenGL;

	};
}