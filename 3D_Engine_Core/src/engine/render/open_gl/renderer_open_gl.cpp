#include <engine/render/open_gl/renderer_open_gl.hpp>

#include <engine/render/open_gl/vertex_array.hpp>
#include <engine/logging/log.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace engine::render
{
	bool renderer_open_gl::init_with_glfw() noexcept
	{
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			LOG_CRITICAL("Can't load glad.");
			return false;
		}
		return true;
	}



	void renderer_open_gl::draw(const vertex_array& _vertex_array_buffer) noexcept
	{
		_vertex_array_buffer.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}



	void renderer_open_gl::setClearColor(uint8_t _red, uint8_t _green, uint8_t _blue, float _alpha) noexcept
	{
		glClearColor(_red, _green, _blue, _alpha);
	}



	void renderer_open_gl::setViewport(uint16_t _width, uint16_t _height, uint16_t _left_offset, uint16_t _bottom_offset) noexcept
	{
		glViewport(_left_offset, _bottom_offset, _width, _height);
	}



	std::string renderer_open_gl::getVendor() noexcept
	{
		return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	}



	std::string renderer_open_gl::getRenderer() noexcept
	{
		return reinterpret_cast<const char*>(glGetString(GL_RENDER));
	}



	std::string renderer_open_gl::getVersion() noexcept
	{
		return reinterpret_cast<const char*>(glGetString(GL_VERSION));
	}
}