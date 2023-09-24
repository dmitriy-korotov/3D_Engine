#pragma once

#include <engine/util/noconstructible.hpp>

#include <memory>



namespace engine::window::glfw
{
	class glfw_window;
}

namespace engine::modules::imgui
{
	class UIModule : private util::noconstructible
	{
	public:

		using window_ptr = std::shared_ptr<window::glfw::glfw_window>;

		static void onGlfwWindowCreate_OpenGLRenderer(const window_ptr& _window_ptr) noexcept;
		static void onGLfwWindowShutdown_OpenGLRenderer() noexcept;
		static void onUIDrawBegin_GlfwWindow_OpenGLRenderer() noexcept;
		static void onUIDrawEnd_GlfwWindow_OpenGLRenderer() noexcept;

		static void createDockSpace();

	private:

		static void setupImGuiConfig() noexcept;

	};
}