#include <engine/ecs/components/render/mesh.hpp>

#include <engine/render/meshes/basic_mesh.hpp>



namespace engine::ecs::components
{
	mesh::mesh(mesh_storage _meshes) noexcept
			: m_meshes(std::move(_meshes))
	{ }



	const mesh::mesh_storage& mesh::getMeshes() const noexcept
	{
		return m_meshes;
	}
}