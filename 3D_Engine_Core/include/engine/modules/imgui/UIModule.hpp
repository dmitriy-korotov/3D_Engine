#pragma once

#include <engine/util/noconstructible.hpp>


struct GLFWwindow;

namespace engine::modules::imgui
{
	class UIModule : private util::noconstructible
	{
	public:

		static void onGlfwWindowCreate_OpenGLRenderer(GLFWwindow* _window_ptr) noexcept;
		static void onGLfwWindowShutdown_OpenGLRenderer() noexcept;
		static void onUIDrawBegin_GlfwWindow_OpenGLRenderer() noexcept;
		static void onUIDrawEnd_GlfwWindow_OpenGLRenderer() noexcept;

		static void ShowExampleAppDockSpace(bool* p_open);

	private:

		static void setupImGuiConfig() noexcept;

	};
}