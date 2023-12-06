#include <engine/render/open_gl/renderer.hpp>

#include <engine/logging/log.hpp>

#include <engine/render/basic_shader_program.hpp>
#include <engine/render/basic_mesh.hpp>
#include <engine/render/material.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace engine::render::open_gl
{
	auto mask_enum_to_GLbitfield(Mask _mask_type) noexcept -> GLbitfield
	{
		switch (_mask_type)
		{
		case Mask::ColorBuffer:			return GL_COLOR_BUFFER_BIT;
		case Mask::DepthBuffer:			return GL_DEPTH_BUFFER_BIT;
		}
		LOG_ERROR("[OpenGL Renderer ERROR] This mask is not found (code: {0})", static_cast<uint8_t>(_mask_type));
		return GL_COLOR_BUFFER_BIT;
	}



	auto drawing_mode_to_GLenum(DrawingMode _drawing_mode) noexcept -> GLenum
	{
		switch (_drawing_mode)
		{
		case DrawingMode::Point:				return GL_POINTS;
		case DrawingMode::Triangle:				return GL_TRIANGLES;
		case DrawingMode::TriangleStrip:		return GL_TRIANGLE_STRIP;
		case DrawingMode::Line:					return GL_LINES;
		case DrawingMode::LineStrip:			return GL_LINE_STRIP;
		}
		LOG_ERROR("[OpenGL Renderer ERROR] This drawing mode is not found (code: {0})", static_cast<uint8_t>(_drawing_mode));
		return GL_TRIANGLES;
	}



	auto GLenum_debug_severity_to_string(GLenum _severity) noexcept -> std::string
	{
		switch (_severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:				return "GL_DEBUG_SEVERITY_HIGH";
		case GL_DEBUG_SEVERITY_MEDIUM:				return "GL_DEBUG_SEVERITY_MEDIUM";
		case GL_DEBUG_SEVERITY_LOW:					return "GL_DEBUG_SEVERITY_LOW";
		case GL_DEBUG_SEVERITY_NOTIFICATION:		return "GL_DEBUG_SEVERITY_NOTIFICATION";
		}
		return "INVALID_SEVERITY_LEVEL";
	}



	auto GLenum_source_message_to_string(GLenum _source) noexcept -> std::string
	{
		switch (_source)
		{
		case GL_DEBUG_SOURCE_API:					return "GL_DEBUG_SOURCE_API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:			return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:		return "GL_DEBUG_SOURCE_SHADER_COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY:			return "GL_DEBUG_SOURCE_THIRD_PARTY";
		case GL_DEBUG_SOURCE_APPLICATION:			return "GL_DEBUG_SOURCE_APPLICATION";
		case GL_DEBUG_SOURCE_OTHER:					return "GL_DEBUG_SOURCE_OTHER";
		}
		return "INVALID_SOURCE_ERROR";
	}



	auto GLenum_message_type_to_string(GLenum _message_type) noexcept -> std::string
	{
		switch (_message_type)
		{
		case GL_DEBUG_TYPE_ERROR:					return "GL_DEBUG_TYPE_ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:		return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:		return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY:				return "GL_DEBUG_TYPE_PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE:				return "GL_DEBUG_TYPE_PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER:					return "GL_DEBUG_TYPE_MARKER";
		case GL_DEBUG_TYPE_PUSH_GROUP:				return "GL_DEBUG_TYPE_PUSH_GROUP";
		default:									return "GL_DEBUG_TYPE_OTHER";
		}
	}





	auto renderer::instance() noexcept -> renderer&
	{
		static renderer instance;
		return instance;
	}



	renderer::renderer() noexcept
	{ }



	auto renderer::init(window::WindowImpl _window_impl) noexcept -> bool
	{
		switch (_window_impl)
		{
		case engine::window::WindowImpl::GLFW:
			if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
			{
				LOG_CRITICAL("[OpenGL Renderer ERROR] Can't load glad with Glfw.");
				return false;
			}
			break;
		case engine::window::WindowImpl::SDL:
			break;
		case engine::window::WindowImpl::SFML:
			break;
		}

#ifndef NDEBUG
		setupDebugContext();
#endif

		m_is_inited = true;

		return true;
	}



	auto renderer::setupDebugContext() noexcept -> void
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(
			[](GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, const GLchar* _message, const void* _userParam) -> void
			{
				switch (_severity)
				{
				case GL_DEBUG_SEVERITY_HIGH:		
					LOG_CRITICAL("[OpenGL ERROR] Severity level: {0}.\nSource massage: {1}.\nMessage type: {2}.\nMessage: {3}",
								 GLenum_debug_severity_to_string(_severity),
								 GLenum_source_message_to_string(_source),
								 GLenum_message_type_to_string(_type),
								 _message);
					break;
				case GL_DEBUG_SEVERITY_MEDIUM:	
					LOG_ERROR("[OpenGL ERROR] Severity level: {0}.\nSource massage: {1}.\nMessage type: {2}.\nMessage: {3}",
							  GLenum_debug_severity_to_string(_severity),
							  GLenum_source_message_to_string(_source),
							  GLenum_message_type_to_string(_type),
							  _message);
					break;
				case GL_DEBUG_SEVERITY_LOW:		
					LOG_WARN("[OpenGL ERROR] Severity level: {0}.\nSource massage: {1}.\nMessage type: {2}.\nMessage: {3}",
							 GLenum_debug_severity_to_string(_severity),
							 GLenum_source_message_to_string(_source),
							 GLenum_message_type_to_string(_type),
							 _message);
					break;
				case GL_DEBUG_SEVERITY_NOTIFICATION:	
					LOG_INFO("[OpenGL ERROR] Severity level: {0}.\nSource massage: {1}.\nMessage type: {2}.\nMessage: {3}",
							 GLenum_debug_severity_to_string(_severity),
							 GLenum_source_message_to_string(_source),
							 GLenum_message_type_to_string(_type),
							 _message);
					break;
				}
			}, nullptr);
	}



	auto renderer::draw(const basic_shader_program& _shader_program, const basic_mesh& _mesh, DrawingMode _drawing_mode) noexcept -> void
	{
		_shader_program.bind();
		_mesh.use();
		glDrawElements(drawing_mode_to_GLenum(_drawing_mode), _mesh.getIndexesCount(), GL_UNSIGNED_INT, nullptr);
	}



	auto renderer::enableDepthTest() noexcept -> void
	{
		glEnable(GL_DEPTH_TEST);
	}



	auto renderer::disableDepthTest() noexcept -> void
	{
		glDisable(GL_DEPTH_TEST);
	}



	auto renderer::setClearColor(float _red, float _green, float _blue, float _alpha) noexcept -> void
	{
		glClearColor(_red, _green, _blue, _alpha);
	}



	auto renderer::clear(Mask _mask_type) noexcept -> void
	{
		glClear(mask_enum_to_GLbitfield(_mask_type));
	}



	auto renderer::clear(std::vector<Mask> _mask_types) noexcept -> void
	{
		GLbitfield masks = 0;
		
		for (Mask mask: _mask_types)
			masks |= mask_enum_to_GLbitfield(mask);
		
		glClear(masks);
	}



	auto renderer::setViewport(uint16_t _width, uint16_t _height, uint16_t _left_offset, uint16_t _bottom_offset) noexcept -> void
	{
		glViewport(_left_offset, _bottom_offset, _width, _height);
	}



	auto renderer::getVendor() noexcept -> std::string
	{
		return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	}



	auto renderer::getRenderer() noexcept -> std::string
	{
		return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	}



	auto renderer::getVersion() noexcept -> std::string
	{
		return reinterpret_cast<const char*>(glGetString(GL_VERSION));
	}
}