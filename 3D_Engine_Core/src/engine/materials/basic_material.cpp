#include <engine/materials/basic_material.hpp>

#include <engine/render/shaders/basic_shader.hpp>



namespace engine::materials
{
	basic_material::basic_material(shader_ptr _shader) noexcept
			: m_shader(std::move(_shader))
	{ }
}