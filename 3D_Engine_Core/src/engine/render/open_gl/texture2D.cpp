#include <engine/render/open_gl/texture2D.hpp>

#include <glad/glad.h>



namespace engine::render::open_gl
{
	texture2D::texture2D() noexcept
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);
	}



	void texture2D::setTextureData(const uint8_t* _data, uint16_t _width, uint16_t _height) noexcept
	{
		m_width = _width;
		m_height = _height;

		glTextureStorage2D(m_texture_id, 1, GL_RGB8, m_width, m_height);
		glTextureSubImage2D(m_texture_id, 0, 0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, _data);
		glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_texture_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}



	void texture2D::bindTexture(uint8_t _target) noexcept
	{
		glBindTextureUnit(_target, m_texture_id);
	}



	texture2D::~texture2D()
	{
		glDeleteTextures(1, &m_texture_id);
	}
}