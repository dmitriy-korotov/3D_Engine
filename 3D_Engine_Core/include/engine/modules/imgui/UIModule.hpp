#pragma once

#include <engine/util/noconstructible.hpp>

#include <memory>



namespace engine::window::glfw
{
	class window;
}

namespace engine::modules::imgui
{
	class UIModule : private util::noconstructible
	{
	public:

		using window_ptr = std::shared_ptr<window::glfw::window>;

		static void onGlfwWindowCreate_OpenGLRenderer(const window_ptr& _window_ptr) noexcept;
		static void onGLfwWindowShutdown_OpenGLRenderer() noexcept;
		static void onUIDrawBegin_GlfwWindow_OpenGLRenderer() noexcept;
		static void onUIDrawEnd_GlfwWindow_OpenGLRenderer() noexcept;

		static void ShowExampleAppDockSpace(bool* p_open);

	private:

		static void setupImGuiConfig() noexcept;

	};
}