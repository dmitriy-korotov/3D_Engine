#include <engine/ecs/components/render/material.hpp>

#include <engine/render/basic_material.hpp>



namespace engine::ecs::components
{
	material::material(material_ptr _material) noexcept
			: m_material(std::move(_material))
	{ }



	const material::material_ptr& material::getMaterial() const noexcept
	{ 
		return m_material;
	}
}