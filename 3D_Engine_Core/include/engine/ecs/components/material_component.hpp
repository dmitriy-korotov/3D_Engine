#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <memory>



namespace engine::render::materials
{
	class basic_material;
}



namespace engine::ecs::components
{
	using render::materials::basic_material;

	class material_component: public basic_component
	{
	public:

		using material_ptr = std::shared_ptr<basic_material>;

		material_component(material_ptr _material) noexcept;

		const material_ptr& getMaterial() const noexcept;

	private:

		material_ptr m_material = nullptr;

	};
}