#include <engine/render/open_gl/texture2D.hpp>

#include <engine/logging/log.hpp>

#include <glad/glad.h>



namespace engine::render::open_gl
{
	constexpr GLenum internal_format_to_GLenum(InternalFormat _internal_format) noexcept
	{
		switch (_internal_format)
		{
		case InternalFormat::RGB_8:
			return GL_RGB8;
		case InternalFormat::RGB_12:
			return GL_RGB12;
		case InternalFormat::RGB_16:
			return GL_RGB16;
		}
		LOG_ERROR("[Texture2D ERROR] This format is not found (code: {0}).", static_cast<uint8_t>(_internal_format));

		return GL_RGB8;
	}



	constexpr GLenum wrap_type_to_GLenum(Wrap _wrap_type) noexcept
	{
		switch (_wrap_type)
		{
		case Wrap::Repeat:
			return GL_REPEAT;
		case Wrap::MirroredRepeat:
			return GL_MIRRORED_REPEAT;
		case Wrap::Clamp:
			return GL_CLAMP;
		case Wrap::ClampToEdge:
			return GL_CLAMP_TO_EDGE;
		case Wrap::ClampToBorder:
			return GL_CLAMP_TO_BORDER;
		}
		LOG_ERROR("[Texture2D ERROR] This wrap type is not found (code: {0}).", static_cast<uint8_t>(_wrap_type));

		return GL_REPEAT;
	}



	constexpr GLenum filter_type_to_GLenum(Filter _filter_type) noexcept
	{
		switch (_filter_type)
		{
		case Filter::Linear:
			return GL_LINEAR;
		}
		LOG_ERROR("[Texture2D ERROR] This filter type is not found (code: {0}).", static_cast<uint8_t>(_filter_type));

		return GL_LINEAR;
	}




	texture2D::texture2D() noexcept
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);
	}



	uint16_t texture2D::getWidth() const noexcept
	{
		return m_width;
	}



	uint16_t texture2D::getHeight() const noexcept
	{
		return m_height;
	}



	void texture2D::setTextureData(const uint8_t* _data, uint16_t _width, uint16_t _height, InternalFormat _internal_format) noexcept
	{
		m_width = _width;
		m_height = _height;

		glTextureStorage2D(m_texture_id, 1, GL_RGB8, m_width, m_height);
		glTextureSubImage2D(m_texture_id, 0, 0, 0, m_width, m_height, internal_format_to_GLenum(_internal_format), GL_UNSIGNED_BYTE, _data);
	}



	void texture2D::setTextureParams(const TextureParamsStorage& _texture_params) noexcept
	{
		glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, wrap_type_to_GLenum(_texture_params.texture_wrap_s));
		glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, wrap_type_to_GLenum(_texture_params.texture_wrap_t));
		glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, filter_type_to_GLenum(_texture_params.texture_min_filter));
		glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, filter_type_to_GLenum(_texture_params.texture_mag_filter));
	}



	void texture2D::bindTexture(uint8_t _target) const noexcept
	{
		glBindTextureUnit(_target, m_texture_id);
	}



	texture2D::~texture2D()
	{
		glDeleteTextures(1, &m_texture_id);
	}
}