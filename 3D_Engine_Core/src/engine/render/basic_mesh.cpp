#include <engine/render/basic_mesh.hpp>



namespace engine::render
{
	basic_mesh::basic_mesh(vertex_storage _vertexes, index_storage _indexes) noexcept
			: m_vertexes(std::move(_vertexes))
			, m_indexes(std::move(_indexes))
	{ }



	basic_mesh::basic_mesh(basic_mesh&& _other) noexcept
			: m_vertexes(std::move(_other.m_vertexes))
			, m_indexes(std::move(_other.m_indexes))
	{ }



	basic_mesh& basic_mesh::operator=(basic_mesh&& _right) noexcept
	{
		m_vertexes = std::move(_right.m_vertexes);
		m_indexes = std::move(_right.m_indexes);
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



	void basic_mesh::setIndexes(index_storage _indexes) noexcept
	{
		m_indexes = std::move(_indexes);
	}



	const basic_mesh::index_storage& basic_mesh::getIndexes() const noexcept
	{
		return m_indexes;
	}



	size_t basic_mesh::getIndexesCount() const noexcept
	{
		return m_indexes.size();
	}



	size_t basic_mesh::getVetexesCount() const noexcept
	{
		return m_vertexes.size();
	}
}