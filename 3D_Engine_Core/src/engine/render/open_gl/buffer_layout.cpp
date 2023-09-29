#include <engine/render/open_gl/buffer_layout.hpp>

#include <engine/logging/log.hpp>

#include <glad/glad.h>



namespace engine::render::open_gl
{
	constexpr uint8_t get_components_count_for_shader_data_type(ShaderDataType _shader_data_type) noexcept
	{
		switch (_shader_data_type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Int:
			return 1;
		case ShaderDataType::Float2:
		case ShaderDataType::Int2:
			return 2;
		case ShaderDataType::Float3:
		case ShaderDataType::Int3:
			return 3;
		case ShaderDataType::Float4:
		case ShaderDataType::Int4:
			return 4;
		}
		LOG_ERROR("[Buffer Layout ERROR] Not found count elements for this shader data type (code: {0}).", static_cast<uint8_t>(_shader_data_type));
		
		return 0;
	}



	constexpr uint32_t get_openGL_type_for_shader_data_type(ShaderDataType _shader_data_type) noexcept
	{
		switch (_shader_data_type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
			return GL_FLOAT;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		}
		LOG_ERROR("[BUFFER LAYOUT ERROR] OpenGL type for this shader data type not found (code: {0}).", static_cast<uint8_t>(_shader_data_type));

		return 0;
	}



	constexpr uint32_t get_sizeof_type_for_shader_data_type(ShaderDataType _shader_data_type) noexcept
	{
		switch (_shader_data_type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
			return sizeof(GLfloat);
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return sizeof(GLint);
		}
		LOG_ERROR("[BUFFER LAYOUT ERROR] Sizeof type for this shader data type not found (code: {0}).", static_cast<uint8_t>(_shader_data_type));

		return 0;
	}



	constexpr size_t get_sizeof_shader_data_type(ShaderDataType _shader_data_type) noexcept
	{
		return get_components_count_for_shader_data_type(_shader_data_type) * get_sizeof_type_for_shader_data_type(_shader_data_type);
	}




	buffer_element::buffer_element(ShaderDataType _shader_data_type) noexcept
			: shader_data_type(_shader_data_type)
			, components_type(get_openGL_type_for_shader_data_type(shader_data_type))
			, components_count(get_components_count_for_shader_data_type(shader_data_type))
			, size(get_sizeof_shader_data_type(shader_data_type))
		    , offset(0)
	{ }




	buffer_layout::buffer_layout(std::initializer_list<buffer_element> _buffer_elements) noexcept
			: m_buffer_elements(std::move(_buffer_elements))
	{
		size_t offset = 0;
		for (auto& elem_ : m_buffer_elements)
		{
			elem_.offset = offset;
			offset += elem_.size;
			m_stride += elem_.size;
		}
	}



	size_t buffer_layout::getStride() const noexcept
	{
		return m_stride;
	}



	const std::vector<buffer_element>& buffer_layout::getElements() const noexcept
	{
		return m_buffer_elements;
	}
}