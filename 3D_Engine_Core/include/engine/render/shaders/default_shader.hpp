#pragma once

#include <engine/render/shaders/basic_shader.hpp>
#include <engine/render/shaders/shader_constructor.hpp>

#include <string>



namespace engine::render::shaders
{
	class default_shader final : public basic_shader
	{
	public:

		static constexpr uint16_t s_GLSLVersion = 460;



		const std::string_view& getVertexShader() const noexcept override;
		const std::string_view& getFragmentShader() const noexcept override;

		uint16_t getGLSLVersion() const noexcept override;

		uint16_t getInputPostionVertexAttrib() const noexcept override;
		std::optional<uint16_t> getInputNormalVertexAttrib() const noexcept override;
		std::optional<uint16_t> getInputTexCoordVertexAttrib() const noexcept override;

		std::optional<std::string_view> getModelViewMatrixName() const noexcept override;
		std::optional<std::string_view> getModelViewPrijectionMatrixName() const noexcept override;
		std::optional<std::string_view> getNormalMatrixName() const noexcept override;

		std::optional<std::string_view> getSourceLightColorName() const noexcept override;
		std::optional<std::string_view> getSourceLightPositionName() const noexcept override;
		std::optional<std::string_view> getAmbientFactorName() const noexcept override;
		std::optional<std::string_view> getSpecularFactorName() const noexcept override;
		std::optional<std::string_view> getDiffuseFactorName() const noexcept override;
		std::optional<std::string_view> getShiniessName() const noexcept override;

		bool textureUnitExists(uint16_t _unit) const noexcept override;

	private:
		
		static constexpr std::string_view m_vertex_shader =
		{
			SHADER_VERISON("460")

			SHADER_DEFINE_INPUT_POSITION_VERTEX_ATTRIBUTE
			SHADER_DEFINE_INPUT_NORMAL_VERTEX_ATTRIBUTE
			SHADER_DEFINE_INPUT_TEXCOORD_VERTEX_ATTRIBUTE

			SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_MODEL_VIEW_TRANSFORM, "mat4")
			SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_MODEL_VIEW_PROJECTION_TRANSFORM, "mat4")
			SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_NORMAL_MATRIX, "mat3")

			SHADER_DEFINE_OUTPUT_TEXCOORD_VERTEX_ATTRIBUTE
			SHADER_DEFINE_OUTPUT_NORMAL_VERTEX_ATTRIBUTE
			SHADER_DEFINE_OUTPUT_POSITION_VERTEX_ATTRIBUTE

			"void main() {\n"
				SHADER_OUT_VERTEX_ATTRIBUTE_TEXCOORD_NAME "=" SHADER_IN_VERTEX_ATTRIBUTE_TEXCOORD_NAME ";\n"
				SHADER_OUT_VERTEX_ATTRIBUTE_NORMAL_NAME "=" SHADER_UNIFORM_NORMAL_MATRIX "*" SHADER_IN_VERTEX_ATTRIBUTE_NORMAL_NAME ";\n"
				"vec4 camera_vertex_position = " SHADER_UNIFORM_MODEL_VIEW_TRANSFORM "* vec4(" SHADER_IN_VERTEX_ATTRIBUTE_POSITION_NAME ", 1.0);\n"
				SHADER_OUT_VERTEX_ATTRIBUTE_POSITION_NAME "= camera_vertex_position.xyz;\n"
				"gl_Position = " SHADER_UNIFORM_MODEL_VIEW_PROJECTION_TRANSFORM "* vec4(" SHADER_IN_VERTEX_ATTRIBUTE_POSITION_NAME ", 1.0);\n"
			"}"
		};



		static constexpr std::string_view m_fragment_shader =
		{
			SHADER_VERISON("460")

			SHADER_DEFINE_INPUT_POSITION_FRAGMENT_ATTRIBUTE
			SHADER_DEFINE_INPUT_NORMAL_FRAGMENT_ATTRIBUTE
			SHADER_DEFINE_INPUT_TEXCOORD_FRAGMENT_ATTRIBUTE

			SHADER_DEFINE_SAMPLER2D("inTexture", "0")

			SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_SOURCE_LIGHT_COLOR, "vec3")
			SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_SOURCE_LIGHT_POSITION, "vec3")
			SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_AMBIENT_FACTOR, "float")
			SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_DIFFUSE_FACTOR, "float")
			SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_SPECULAR_FACTOR, "float")
			SHADER_DEFINE_UNIFORM(SHADER_UNIFORM_SHINIESS, "float")

			SHADER_DEFINE_OUTPUT_COLOR_FRAGMENT_ATTRIBUTE

			"void main() {\n"
				"vec3 normal = normalize(" SHADER_IN_FRAGMENT_ATTRIBUTE_NORMAL_NAME ";\n"
				
				"vec3 lightDirection = normalize(" SHADER_UNIFORM_SOURCE_LIGHT_POSITION "-" SHADER_IN_FRAGMENT_ATTRIBUTE_POSITION_NAME ");\n"
				"vec3 reflectDirection = reflect(-lightDirection, normal);\n"
				"vec3 directionInCamera = normalize(-" SHADER_IN_FRAGMENT_ATTRIBUTE_POSITION_NAME ");\n"
			
				"vec3 ambientLight = " SHADER_UNIFORM_AMBIENT_FACTOR "*" SHADER_UNIFORM_SOURCE_LIGHT_COLOR ";\n"
				"vec3 diffuseLight = " SHADER_UNIFORM_DIFFUSE_FACTOR "*" SHADER_UNIFORM_SOURCE_LIGHT_COLOR "* max(dot(normal, lightDirection), 0.0);\n"
				"vec3 reflectionLight = " SHADER_UNIFORM_SPECULAR_FACTOR " * " SHADER_UNIFORM_SOURCE_LIGHT_COLOR "* pow(max(dot(reflectDirection, directionInCamera), 0.0), " SHADER_UNIFORM_SHINIESS ");\n"
				
				"vec4 light = vec4((ambientLight + diffuseLight + reflectionLight), 1.f);\n"
				SHADER_OUT_FRAGMENT_ATTRIBUTE_COLOR_NAME "= light * texture(inTexture, " SHADER_IN_FRAGMENT_ATTRIBUTE_TEXCOORD_NAME ");\n"
			"}"
		};
	};
}