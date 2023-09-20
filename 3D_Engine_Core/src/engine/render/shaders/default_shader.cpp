#include <engine/render/shaders/default_shader.hpp>



static constexpr uint8_t s_vertex_position_layout = 0;
static constexpr uint8_t s_vertex_normal_layout = 1;
static constexpr uint8_t s_vertex_texture_coord_layout = 2;

static constexpr uint8_t s_first_texture_layout = 0;



namespace engine::render::shaders
{
	const std::string_view& default_shader::getVertexShader() const noexcept
	{
		return m_fragment_shader;
	}



	const std::string_view& default_shader::getFragmentShader() const noexcept
	{
		return m_fragment_shader;
	}



	uint16_t default_shader::getGLSLVersion() const noexcept
	{
		return s_GLSLVersion;
	}



	uint16_t default_shader::getInputPostionVertexAttrib() const noexcept
	{
		return s_vertex_position_layout;
	}



	std::optional<uint16_t> default_shader::getInputNormalVertexAttrib() const noexcept
	{
		return s_vertex_normal_layout;
	}



	std::optional<uint16_t> default_shader::getInputTexCoordVertexAttrib() const noexcept
	{
		return s_vertex_texture_coord_layout;
	}



	std::optional<std::string_view> default_shader::getModelViewMatrixName() const noexcept
	{
		return SHADER_UNIFORM_MODEL_VIEW_TRANSFORM;
	}



	std::optional<std::string_view> default_shader::getModelViewPrijectionMatrixName() const noexcept
	{
		return SHADER_UNIFORM_MODEL_VIEW_PROJECTION_TRANSFORM;
	}



	std::optional<std::string_view> default_shader::getNormalMatrixName() const noexcept
	{
		return SHADER_UNIFORM_NORMAL_MATRIX;
	}



	std::optional<std::string_view> default_shader::getSourceLightColorName() const noexcept
	{
		return SHADER_UNIFORM_SOURCE_LIGHT_COLOR;
	}



	std::optional<std::string_view> default_shader::getSourceLightPositionName() const noexcept
	{
		return SHADER_UNIFORM_SOURCE_LIGHT_POSITION;
	}



	std::optional<std::string_view> default_shader::getAmbientFactorName() const noexcept
	{
		return SHADER_UNIFORM_AMBIENT_FACTOR;
	}



	std::optional<std::string_view> default_shader::getSpecularFactorName() const noexcept
	{
		return SHADER_UNIFORM_SPECULAR_FACTOR;
	}



	std::optional<std::string_view> default_shader::getDiffuseFactorName() const noexcept
	{
		return SHADER_UNIFORM_DIFFUSE_FACTOR;
	}



	std::optional<std::string_view> default_shader::getShiniessName() const noexcept
	{
		return SHADER_UNIFORM_SHINIESS;
	}



	bool default_shader::textureUnitExists(uint16_t _unit) const noexcept
	{
		return (_unit == s_first_texture_layout);
	}
}