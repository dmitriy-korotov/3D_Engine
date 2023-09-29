#pragma once

#include <stdint.h>
#include <string>
#include <functional>



namespace engine::render
{
	class image;
}

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

typedef void (*GLFWwindowsizefun)(GLFWwindow* window, int width, int height);
typedef void (*GLFWwindowclosefun)(GLFWwindow* window);
typedef void (*GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);
typedef void (*GLFWmousebuttonfun)(GLFWwindow* window, int button, int action, int mods);

namespace engine::window::glfw
{
	class glfw;

	struct monitor
	{
		friend glfw;

		monitor(GLFWmonitor* _monitor_ptr) noexcept;

	private:

		GLFWmonitor* m_monitor_ptr = nullptr;

	};



	struct video_mode
	{
		friend glfw;

		video_mode(const GLFWvidmode* _video_mode_ptr) noexcept;

		int redBits() const noexcept;
		int greenBits() const noexcept;
		int blueBits() const noexcept;
		int refreshRate() const noexcept;

	private:

		const GLFWvidmode* m_video_mode_ptr = nullptr;

	};



	enum class WindowHint : uint8_t
	{
		RedBits,
		GreenBits,
		BlueBits,
		RefreshRate
	};



	class glfw
	{
	public:

		static glfw& instance() noexcept;

		glfw() = default;

		void init() noexcept;
		void terminate() noexcept;
		void getCurrentCursorPosition(GLFWwindow* _window_ptr, double& _x, double& _y) const noexcept;
		void setWindowIcon(GLFWwindow* _window_ptr, render::image& _icon) const noexcept;
		void pollEvents() const noexcept;
		void makeContextCurrent(GLFWwindow* _window_ptr) const noexcept;
		void swapBuffers(GLFWwindow* _window_ptr) const noexcept;
		monitor getPrimaryMonitor() const noexcept;
		video_mode getVideoMode(const monitor& _monitor) const noexcept;
		void windowHint(WindowHint _hint, int _value) const noexcept;
		GLFWwindow* createWindow(uint16_t _width, uint16_t _height, const std::string_view& _title,
								 const monitor& _monitor, GLFWwindow* _share = nullptr) const noexcept;

		void setWindowResizeCallBack(GLFWwindow* _window_ptr, GLFWwindowsizefun _call_back) const noexcept;
		void setWindowCloseCallBack(GLFWwindow* _window_ptr, GLFWwindowclosefun _call_back) const noexcept;
		void setKeyCallback(GLFWwindow* _window_ptr, GLFWkeyfun _call_back) const noexcept;
		void setMouseButtonCallback(GLFWwindow* _window_ptr, GLFWmousebuttonfun _call_back) const noexcept;

		void destroyWindow(GLFWwindow* _window_ptr) const noexcept;

		bool isInited() const noexcept;

	private:

		bool m_is_inited = false;

	};
}