#include <engine/ecs/components/render/material_component.hpp>

#include <engine/render/materials/basic_material.hpp>



namespace engine::ecs::components
{
	material_component::material_component(material_ptr _material) noexcept
			: m_material(std::move(_material))
	{ }



	const material_component::material_ptr& material_component::getMaterial() const noexcept
	{ 
		return m_material;
	}
}