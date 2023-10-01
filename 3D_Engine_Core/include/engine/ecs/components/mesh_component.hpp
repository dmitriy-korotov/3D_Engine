#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <vector>



namespace engine::render
{
	class basic_mesh;
}



namespace engine::ecs::components
{
	using render::basic_mesh;

	class mesh_component : public basic_component
	{
	public:

		using mesh_storage = std::vector<basic_mesh>;

		mesh_component(mesh_storage _meshes) noexcept;

		const mesh_storage& getMeshes() const noexcept;

	private:

		mesh_storage m_meshes;

	};
}