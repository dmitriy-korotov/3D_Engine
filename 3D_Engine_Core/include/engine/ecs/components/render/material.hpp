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



		using material_ptr_t = std::shared_ptr<render::material>;

		material() = default;
		material(std::string_view _material_name) noexcept;

		bool setMaterial(std::string_view _material_name) noexcept;
		const material_ptr_t& getMaterial() const noexcept;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	private:

		std::string m_material_name;
		material_ptr_t m_material = nullptr;

	};
}