#include <engine/window/glfw/glfw.hpp>

#include <engine/logging/log.hpp>

#include <GLFW/glfw3.h>



namespace engine::window::glfw
{
	glfw& glfw::instance() noexcept
	{
		static glfw instance;
		return instance;
	}



	glfw::glfw()
	{
		if (!glfwInit())
		{
			LOG_CRITICAL("[Glfw ERROR] Can't initializate glfw.");
		}
		glfwSetErrorCallback(
			[](int _error_code, const char* _description) -> void
			{
				LOG_ERROR("[Glfw ERROR] (code: {0}): {1}", _error_code, _description);
			});
		m_is_inited = true;
	}



	bool glfw::isInited() const noexcept
	{
		return m_is_inited;
	}



	glfw::~glfw()
	{
		glfwTerminate();
	}
}