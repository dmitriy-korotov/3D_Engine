#include <engine/render/open_gl/renderer_open_gl.hpp>

#include <engine/logging/log.hpp>

#include <engine/render/basic_shader_program.hpp>
#include <engine/render/meshes/basic_mesh.hpp>
#include <engine/render/materials/basic_material.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace engine::render::open_gl
{
	GLbitfield mask_enum_to_GLbitfield(renderer::Mask _mask_type) noexcept
	{
		switch (_mask_type)
		{
		case renderer::Mask::ColorBuffer:			return GL_COLOR_BUFFER_BIT;
		case renderer::Mask::DepthBuffer:			return GL_DEPTH_BUFFER_BIT;
		}
		LOG_ERROR("[OpenGL Renderer ERROR] This mask is not found (code: {0})", static_cast<uint8_t>(_mask_type));
		return GL_COLOR_BUFFER_BIT;
	}



	GLenum drawing_mode_to_GLenum(renderer::DrawingMode _drawing_mode) noexcept
	{
		switch (_drawing_mode)
		{
		case renderer::DrawingMode::Point:				return GL_POINTS;
		case renderer::DrawingMode::Triangle:			return GL_TRIANGLES;
		case renderer::DrawingMode::TriangleStrip:		return GL_TRIANGLE_STRIP;
		case renderer::DrawingMode::Line:				return GL_LINES;
		case renderer::DrawingMode::LineStrip:			return GL_LINE_STRIP;
		}
		LOG_ERROR("[OpenGL Renderer ERROR] This drawing mode is not found (code: {0})", static_cast<uint8_t>(_drawing_mode));
		return GL_TRIANGLES;
	}



	std::string GLenum_debug_severity_to_string(GLenum _severity) noexcept
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



	std::string GLenum_source_message_to_string(GLenum _source) noexcept
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



	std::string GLenum_message_type_to_string(GLenum _message_type) noexcept
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





	renderer& renderer::instance() noexcept
	{
		static renderer instance;
		return instance;
	}



	bool renderer::init(window::WindowImpl _window_impl) noexcept
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



	void renderer::setupDebugContext() noexcept
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



	void renderer::draw(const basic_shader_program& _shader_program, const basic_mesh& _mesh,
						const basic_material& _material, DrawingMode _drawing_mode) noexcept
	{
		_shader_program.bind();
		_material.use();
		
		//glDrawElements(drawing_mode_to_GLenum(_drawing_mode), _vertex_array_buffer.getIndexesCount(), GL_UNSIGNED_INT, nullptr);
	}



	void renderer::enableDepthTest() noexcept
	{
		glEnable(GL_DEPTH_TEST);
	}



	void renderer::disableDepthTest() noexcept
	{
		glDisable(GL_DEPTH_TEST);
	}



	void renderer::setClearColor(float _red, float _green, float _blue, float _alpha) noexcept
	{
		glClearColor(_red, _green, _blue, _alpha);
	}



	void renderer::clear(Mask _mask_type) noexcept
	{
		glClear(mask_enum_to_GLbitfield(_mask_type));
	}



	void renderer::clear(std::vector<Mask> _mask_types) noexcept
	{
		GLbitfield masks = 0;
		for (Mask mask: _mask_types)
		{
			masks |= mask_enum_to_GLbitfield(mask);
		}
		glClear(masks);
	}



	void renderer::setViewport(uint16_t _width, uint16_t _height, uint16_t _left_offset, uint16_t _bottom_offset) noexcept
	{
		glViewport(_left_offset, _bottom_offset, _width, _height);
	}



	std::string renderer::getVendor() noexcept
	{
		return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	}



	std::string renderer::getRenderer() noexcept
	{
		return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	}



	std::string renderer::getVersion() noexcept
	{
		return reinterpret_cast<const char*>(glGetString(GL_VERSION));
	}
}