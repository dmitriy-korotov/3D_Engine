#include <engine/render/basic_shader_program.hpp>



namespace engine::render
{
	basic_shader_program::basic_shader_program(basic_shader_program&& _other) noexcept
			: m_is_compiled(_other.m_is_compiled)
	{
		_other.m_is_compiled = false;
	}



	basic_shader_program& basic_shader_program::operator=(basic_shader_program&& _right) noexcept
	{
		m_is_compiled = _right.m_is_compiled;
		_right.m_is_compiled = false;
		return *this;
	}



	bool basic_shader_program::isCompiled() const noexcept
	{
		return m_is_compiled;
	}
}