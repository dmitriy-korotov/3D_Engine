#include <engine/ecs/components/mesh_component.hpp>



namespace engine::ecs::components
{
	mesh_component::mesh_component(mesh_storage _meshes) noexcept
			: m_meshes(std::move(_meshes))
	{ }



	const mesh_component::mesh_storage& mesh_component::getMeshes() const noexcept
	{
		return m_meshes;
	}
}