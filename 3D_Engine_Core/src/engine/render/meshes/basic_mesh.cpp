#include <engine/render/meshes/basic_mesh.hpp>



namespace engine::render::meshes
{
	basic_mesh::basic_mesh(vertex_storage _vertexes) noexcept
			: m_vertexes(std::move(_vertexes))
	{ }



	basic_mesh::basic_mesh(basic_mesh&& _other) noexcept
			: m_vertexes(std::move(_other.m_vertexes))
	{ }



	basic_mesh& basic_mesh::operator=(basic_mesh&& _right) noexcept
	{
		m_vertexes = std::move(_right.m_vertexes);
		return *this;
	}



	void basic_mesh::setVertexes(vertex_storage _vertexes) noexcept
	{
		m_vertexes = std::move(_vertexes);
	}



	const basic_mesh::vertex_storage& basic_mesh::getVertexes() const noexcept
	{
		return m_vertexes;
	}
}