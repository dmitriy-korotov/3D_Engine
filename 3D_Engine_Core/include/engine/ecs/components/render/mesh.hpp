#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <engine/render/fwd/basic_mesh.hpp>

#include <vector>
#include <memory>



namespace engine::ecs::components
{
	class mesh: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "mesh";



		using mesh_ptr = std::shared_ptr<render::basic_mesh>;
		using mesh_storage = std::vector<mesh_ptr>;

		mesh(mesh_storage _meshes) noexcept;

		const mesh_storage& getMeshes() const noexcept;

	private:

		mesh_storage m_meshes;

	};
}