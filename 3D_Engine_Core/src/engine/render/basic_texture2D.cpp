#include <engine/render/basic_texture2D.hpp>



namespace engine::render
{
	basic_texture2D::basic_texture2D(basic_texture2D&& _other) noexcept
			: m_height(_other.m_height)
			, m_width(_other.m_width)
			, m_texture_parametrs(_other.m_texture_parametrs)
			, m_internal_format(_other.m_internal_format)
	{ 
		_other.m_height = 0;
		_other.m_width = 0;
	}



	auto basic_texture2D::operator=(basic_texture2D&& _right) noexcept -> basic_texture2D&
	{
		m_height = _right.m_height;
		m_width = _right.m_width;
		m_internal_format = _right.m_internal_format;
		m_texture_parametrs = _right.m_texture_parametrs;
		_right.m_height = 0;
		_right.m_width = 0;
		return *this;
	}



	auto basic_texture2D::getWidth() const noexcept -> uint16_t
	{
		return m_width;
	}



	auto basic_texture2D::getHeight() const noexcept -> uint16_t
	{
		return m_height;
	}



	auto basic_texture2D::getInternalFormat() const noexcept -> InternalFormat
	{
		return m_internal_format;
	}



	auto basic_texture2D::getWrapT() const noexcept -> Wrap
	{
		return m_texture_parametrs.texture_wrap_t;
	}



	auto basic_texture2D::getWrapS() const noexcept -> Wrap
	{
		return m_texture_parametrs.texture_wrap_s;
	}



	auto basic_texture2D::getMinFilter() const noexcept -> Filter
	{
		return m_texture_parametrs.texture_min_filter;
	}



	auto basic_texture2D::getMagFilter() const noexcept -> Filter
	{
		return m_texture_parametrs.texture_mag_filter;
	}
}