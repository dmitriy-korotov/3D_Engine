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
		case Filter::LinearMipMapLinear:
			return GL_LINEAR_MIPMAP_LINEAR;
		case Filter::LinearMipMapNearest:
			return GL_LINEAR_MIPMAP_NEAREST;
		case Filter::NearestMipMapLinear:
			return GL_NEAREST_MIPMAP_LINEAR;
		case Filter::NearestMipMapNearest:
			return GL_NEAREST_MIPMAP_NEAREST;
		case Filter::Nearest:
			return GL_NEAREST;
		}
		LOG_ERROR("[Texture2D ERROR] This filter type is not found (code: {0}).", static_cast<uint8_t>(_filter_type));

		return GL_LINEAR;
	}




	texture2D::texture2D() noexcept
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
	}



	texture2D::texture2D(texture2D&& _other) noexcept
			: m_id(_other.m_id)
			, m_height(_other.m_height)
			, m_width(_other.m_width)
	{
		_other.m_height = 0;
		_other.m_width = 0;
		_other.m_id = 0;
	}



	texture2D& texture2D::operator=(texture2D&& _right) noexcept
	{
		if (m_id != _right.m_id)
		{
			glDeleteTextures(1, &m_id);

			m_id = _right.m_id;
			m_width = _right.m_width;
			m_height = _right.m_height;

			_right.m_height = 0;
			_right.m_width = 0;
			_right.m_id = 0;
		}
		return *this;
	}



	uint16_t texture2D::getWidth() const noexcept
	{
		return m_width;
	}



	uint16_t texture2D::getHeight() const noexcept
	{
		return m_height;
	}



	void texture2D::setData(const uint8_t* _data, uint16_t _width, uint16_t _height, InternalFormat _internal_format) noexcept
	{
		m_width = _width;
		m_height = _height;

		GLsizei mip_map_levels = static_cast<GLsizei>(std::log2(std::max(_width, _height))) + 1;
		glTextureStorage2D(m_id, mip_map_levels, internal_format_to_GLenum(_internal_format), m_width, m_height);
		glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, _data);
		glGenerateTextureMipmap(m_id);
	}



	void texture2D::setParametrs(const TextureParamsStorage& _texture_params) noexcept
	{
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, wrap_type_to_GLenum(_texture_params.texture_wrap_s));
		glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, wrap_type_to_GLenum(_texture_params.texture_wrap_t));
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, filter_type_to_GLenum(_texture_params.texture_min_filter));
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, filter_type_to_GLenum(_texture_params.texture_mag_filter));
	}



	void texture2D::bind(uint8_t _unit) const noexcept
	{
		glBindTextureUnit(_unit, m_id);
	}



	texture2D::~texture2D()
	{
		glDeleteTextures(1, &m_id);
	}
}