#include <engine/render/open_gl/buffer_layout.hpp>

#include <engine/logging/log.hpp>

#include <glad/glad.h>



namespace engine::render
{
	constexpr uint8_t get_components_count_for_shader_data_type(ShaderDataType _shader_data_type) noexcept
	{
		switch (_shader_data_type)
		{
		case engine::render::ShaderDataType::Float:
		case engine::render::ShaderDataType::Int:
			return 1;
		case engine::render::ShaderDataType::Float2:
		case engine::render::ShaderDataType::Int2:
			return 2;
		case engine::render::ShaderDataType::Float3:
		case engine::render::ShaderDataType::Int3:
			return 3;
		case engine::render::ShaderDataType::Float4:
		case engine::render::ShaderDataType::Int4:
			return 4;
		}
		LOG_ERROR("Not found count elements for this shader data type (code: {0}).", static_cast<uint8_t>(_shader_data_type));
		
		return 0;
	}



	constexpr std::uint32_t get_openGL_type_for_shader_data_type(ShaderDataType _shader_data_type) noexcept
	{
		switch (_shader_data_type)
		{
		case engine::render::ShaderDataType::Float:
		case engine::render::ShaderDataType::Float2:
		case engine::render::ShaderDataType::Float3:
		case engine::render::ShaderDataType::Float4:
			return GL_FLOAT;
		case engine::render::ShaderDataType::Int:
		case engine::render::ShaderDataType::Int2:
		case engine::render::ShaderDataType::Int3:
		case engine::render::ShaderDataType::Int4:
			return GL_INT;
		}
		LOG_ERROR("OpenGL type for this shader data type not found (code: {0}).", static_cast<uint8_t>(_shader_data_type));

		return 0;
	}



	constexpr std::uint32_t get_sizeof_type_for_shader_data_type(ShaderDataType _shader_data_type) noexcept
	{
		switch (_shader_data_type)
		{
		case engine::render::ShaderDataType::Float:
		case engine::render::ShaderDataType::Float2:
		case engine::render::ShaderDataType::Float3:
		case engine::render::ShaderDataType::Float4:
			return sizeof(GLfloat);
		case engine::render::ShaderDataType::Int:
		case engine::render::ShaderDataType::Int2:
		case engine::render::ShaderDataType::Int3:
		case engine::render::ShaderDataType::Int4:
			return sizeof(GLint);
		}
		LOG_ERROR("Sizeof type for this shader data type not found (code: {0}).", static_cast<uint8_t>(_shader_data_type));

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
			: m_buffer_elements_(std::move(_buffer_elements))
	{
		size_t offset = 0;
		for (auto& elem_ : m_buffer_elements_)
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
		return m_buffer_elements_;
	}
}