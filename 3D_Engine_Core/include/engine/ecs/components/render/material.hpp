#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <engine/render/fwd/material.hpp>

#include <memory>



namespace engine::ecs::components
{
	class material: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "material";



		using material_ptr = std::shared_ptr<render::material>;

		material(material_ptr _material) noexcept;

		void setMaterial(material_ptr _material) noexcept;
		const material_ptr& getMaterial() const noexcept;

	private:

		material_ptr m_material = nullptr;

	};
}