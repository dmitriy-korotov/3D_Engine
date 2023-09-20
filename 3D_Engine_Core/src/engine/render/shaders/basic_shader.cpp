#include <engine/render/shaders/basic_shader.hpp>



namespace engine::render::shaders
{
	std::optional<uint16_t> basic_shader::getInputNormalVertexAttrib() const noexcept { return std::nullopt; }
	std::optional<uint16_t> basic_shader::getInputTexCoordVertexAttrib() const noexcept { return std::nullopt; }

	std::optional<std::string_view> basic_shader::getModelViewMatrixName() const noexcept { return std::nullopt; }
	std::optional<std::string_view> basic_shader::getModelViewPrijectionMatrixName() const noexcept { return std::nullopt; }
	std::optional<std::string_view> basic_shader::getNormalMatrixName() const noexcept { return std::nullopt; }
	std::optional<std::string_view> basic_shader::getSourceLightColorName() const noexcept { return std::nullopt; }
	std::optional<std::string_view> basic_shader::getSourceLightPositionName() const noexcept { return std::nullopt; }
	std::optional<std::string_view> basic_shader::getAmbientFactorName() const noexcept { return std::nullopt; }
	std::optional<std::string_view> basic_shader::getSpecularFactorName() const noexcept { return std::nullopt; }
	std::optional<std::string_view> basic_shader::getDiffuseFactorName() const noexcept { return std::nullopt; }
	std::optional<std::string_view> basic_shader::getShiniessName() const noexcept { return std::nullopt; }

	bool basic_shader::textureUnitExists(uint16_t _unit) const noexcept { return false; }
}