#include <engine/render/meshes/basic_mesh.hpp>



namespace engine::render::meshes
{
	basic_mesh::basic_mesh(vertex_storage _vertexes) noexcept
			: m_vertexes(std::move(_vertexes))
	{ }



	void basic_mesh::setVertexes(vertex_storage _vertexes) noexcept
	{
		m_vertexes = std::move(_vertexes);
	}



	const basic_mesh::vertex_storage& basic_mesh::getVertexes() const noexcept
	{
		return m_vertexes;
	}
}