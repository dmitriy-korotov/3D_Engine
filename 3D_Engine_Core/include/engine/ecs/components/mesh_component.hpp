#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <vector>
#include <memory>



namespace engine::render::meshes
{
	class basic_mesh;
}



namespace engine::ecs::components
{
	using render::meshes::basic_mesh;

	class mesh_component : public basic_component
	{
	public:

		static constexpr std::string_view component_name = "mesh_component";



		using mesh_ptr = std::shared_ptr<basic_mesh>;
		using mesh_storage = std::vector<mesh_ptr>;

		mesh_component(mesh_storage _meshes) noexcept;

		const mesh_storage& getMeshes() const noexcept;

	private:

		mesh_storage m_meshes;

	};
}