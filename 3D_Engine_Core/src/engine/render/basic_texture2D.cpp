#include <engine/render/basic_texture2D.hpp>



namespace engine::render
{
	basic_texture2D::basic_texture2D(basic_texture2D&& _other) noexcept
			: m_height(_other.m_height)
			, m_width(_other.m_width)
	{ 
		m_height = 0;
		m_width = 0;
	}



	basic_texture2D& basic_texture2D::operator=(basic_texture2D&& _right) noexcept
	{
		m_height = _right.m_height;
		m_width = _right.m_width;
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
}