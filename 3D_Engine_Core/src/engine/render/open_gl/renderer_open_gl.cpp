#include <engine/render/open_gl/renderer_open_gl.hpp>

#include <engine/render/open_gl/vertex_array.hpp>
#include <engine/logging/log.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace engine::render
{

	GLbitfield mask_enum_to_GLbifield(renderer_open_gl::Mask _mask_type) noexcept
	{
		switch (_mask_type)
		{
		case engine::render::renderer_open_gl::Mask::ColorBuffer:
			return GL_COLOR_BUFFER_BIT;
		}
		LOG_ERROR("This mask is not found (code: {0})", static_cast<uint8_t>(_mask_type));
		return GL_COLOR_BUFFER_BIT;
	}



	GLenum drawing_mode_to_GLenum(renderer_open_gl::DrawingMode _drawing_mode) noexcept
	{
		switch (_drawing_mode)
		{
		case engine::render::renderer_open_gl::DrawingMode::Triangle:
			return GL_TRIANGLES;
		case engine::render::renderer_open_gl::DrawingMode::Line:
			return GL_LINE;
		}
		LOG_ERROR("This drawing mode is not found (code: {0})", static_cast<uint8_t>(_drawing_mode));
		return GL_TRIANGLES;
	}





	bool renderer_open_gl::init_with_glfw() noexcept
	{
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			LOG_CRITICAL("Can't load glad.");
			return false;
		}
		LOG_INFO("OpenGL vendor: {0}", renderer_open_gl::getVendor());
		LOG_INFO("OpenGL renderer: {0}", renderer_open_gl::getRenderer());
		LOG_INFO("OpenGL version: {0}", renderer_open_gl::getVersion());

		return true;
	}



	void renderer_open_gl::draw(const vertex_array& _vertex_array_buffer, DrawingMode _drawing_mode) noexcept
	{
		_vertex_array_buffer.bind();
		glDrawElements(drawing_mode_to_GLenum(_drawing_mode), _vertex_array_buffer.getIndexesCount(), GL_UNSIGNED_INT, nullptr);
	}



	void renderer_open_gl::setClearColor(uint8_t _red, uint8_t _green, uint8_t _blue, float _alpha) noexcept
	{
		glClearColor(_red, _green, _blue, _alpha);
	}



	void renderer_open_gl::clear(Mask _mask_type) noexcept
	{
		glClear(mask_enum_to_GLbifield(_mask_type));
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
		return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	}



	std::string renderer_open_gl::getVersion() noexcept
	{
		return reinterpret_cast<const char*>(glGetString(GL_VERSION));
	}
}