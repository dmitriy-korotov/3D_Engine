#include <engine/render/basic_texture2D.hpp>



namespace engine::render
{
	basic_texture2D::basic_texture2D(basic_texture2D&& _other) noexcept
			: m_height(_other.m_height)
			, m_width(_other.m_width)
			, m_texture_parametrs(_other.m_texture_parametrs)
			, m_internal_format(_other.m_internal_format)
	{ 
		m_height = 0;
		m_width = 0;
	}



	basic_texture2D& basic_texture2D::operator=(basic_texture2D&& _right) noexcept
	{
		m_height = _right.m_height;
		m_width = _right.m_width;
		m_internal_format = _right.m_internal_format;
		m_texture_parametrs = _right.m_texture_parametrs;
		_right.m_height = 0;
		_right.m_width = 0;
		return *this;
	}



	uint16_t basic_texture2D::getWidth() const noexcept
	{
		return m_width;
	}



	uint16_t basic_texture2D::getHeight() const noexcept
	{
		return m_height;
	}



	InternalFormat basic_texture2D::getInternalFormat() const noexcept
	{
		return m_internal_format;
	}



	Wrap basic_texture2D::getWrapT() const noexcept
	{
		return m_texture_parametrs.texture_wrap_t;
	}



	Wrap basic_texture2D::getWrapS() const noexcept
	{
		return m_texture_parametrs.texture_wrap_s;
	}



	Filter basic_texture2D::getMinFilter() const noexcept
	{
		return m_texture_parametrs.texture_min_filter;
	}



	Filter basic_texture2D::getMagFilter() const noexcept
	{
		return m_texture_parametrs.texture_mag_filter;
	}
}