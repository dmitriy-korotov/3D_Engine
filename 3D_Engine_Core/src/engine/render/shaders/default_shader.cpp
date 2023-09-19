#include <engine/render/shaders/default_shader.hpp>


namespace engine::render::shaders
{
	const std::string_view& default_shader::getVertexShader() noexcept
	{
		return m_fragment_shader;
	}



	const std::string_view& default_shader::getFragmentShader() noexcept
	{
		return m_fragment_shader;
	}
}