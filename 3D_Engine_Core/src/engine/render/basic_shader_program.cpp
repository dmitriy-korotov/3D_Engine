#include <engine/render/basic_shader_program.hpp>



namespace engine::render
{
	basic_shader_program::basic_shader_program(basic_shader_program&& _other) noexcept
			: m_is_compiled(_other.m_is_compiled)
	{
		_other.m_is_compiled = false;
	}



	auto basic_shader_program::operator=(basic_shader_program&& _right) noexcept -> basic_shader_program&
	{
		m_is_compiled = _right.m_is_compiled;
		_right.m_is_compiled = false;
		return *this;
	}



	auto basic_shader_program::isCompiled() const noexcept -> bool
	{
		return m_is_compiled;
	}
}