#pragma once

#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

#include <memory>



namespace engine::render
{
	namespace open_gl
	{
		class shader_program;
	}
	namespace shaders
	{
		class basic_shader;
	}
}



namespace engine::materials
{
	class basic_material
	{
	public:

		using shader_program_ptr = std::shared_ptr<render::open_gl::shader_program>;
		using shader_ptr = std::unique_ptr<render::shaders::basic_shader>;

		basic_material(shader_ptr _shader) noexcept;
		virtual ~basic_material() = default;

		virtual void use() const noexcept = 0;
		virtual void unuse() const noexcept = 0;

		virtual void setModelViewMatirx() const noexcept = 0;
		virtual void setNormalMatrix() const noexcept = 0;
		virtual void setModelViewProjectionMatrix() const noexcept = 0;

		virtual void setSourceLight(const glm::vec3& _light_position, const glm::vec3& _light_color) const noexcept = 0;

		virtual void setAmbientFactor(float _ambient_factor) const noexcept = 0;
		virtual void setDiffuseFactor(float _diffuse_factor) const noexcept = 0;
		virtual void setSpecularFactor(float _specualr_factor) const noexcept = 0;
		virtual void setShiniess(float _shiniess) const noexcept = 0;

	private:

		shader_ptr m_shader = nullptr;

	};
}