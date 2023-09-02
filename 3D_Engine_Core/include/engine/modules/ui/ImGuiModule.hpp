#pragma once



struct GLFWwindow;

namespace engine::ui
{
	class ImGuiModule
	{
	public:

		ImGuiModule() = delete;

		static void onWindowCreate(GLFWwindow* _window_ptr) noexcept;
		static void onWindowShutdown() noexcept;
		static void onUIDrawBegin() noexcept;
		static void onUIDrawEnd() noexcept;

		static void ShowExampleAppDockSpace(bool* p_open);

	};
}