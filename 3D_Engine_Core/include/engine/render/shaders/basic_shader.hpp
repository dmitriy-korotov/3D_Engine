#pragma once

#include <engine/util/nocopyeble.hpp>

#include <string>
#include <optional>



namespace engine::render::shaders
{
	class basic_shader : util::nocopyeble
	{
	public:

		basic_shader() = default;
		virtual ~basic_shader() = default;

		virtual const std::string_view& getVertexShader() const noexcept = 0;
		virtual const std::string_view& getFragmentShader() const noexcept = 0;

		virtual uint16_t getGLSLVersion() const noexcept = 0;

		virtual uint16_t getInputPostionVertexAttrib() const noexcept = 0;
		virtual std::optional<uint16_t> getInputNormalVertexAttrib() const noexcept;
		virtual std::optional<uint16_t> getInputTexCoordVertexAttrib() const noexcept;

		virtual std::optional<std::string_view> getModelViewMatrixName() const noexcept;
		virtual std::optional<std::string_view> getModelViewPrijectionMatrixName() const noexcept;
		virtual std::optional<std::string_view> getNormalMatrixName() const noexcept;

		virtual std::optional<std::string_view> getSourceLightColorName() const noexcept;
		virtual std::optional<std::string_view> getSourceLightPositionName() const noexcept;
		virtual std::optional<std::string_view> getAmbientFactorName() const noexcept;
		virtual std::optional<std::string_view> getSpecularFactorName() const noexcept;
		virtual std::optional<std::string_view> getDiffuseFactorName() const noexcept;
		virtual std::optional<std::string_view> getShiniessName() const noexcept;

		virtual bool textureUnitExists(uint16_t _unit) const noexcept;
	};
}