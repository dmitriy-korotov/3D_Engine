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



	auto basic_mesh::operator=(basic_mesh&& _right) noexcept -> basic_mesh&
	{
		m_vertexes = std::move(_right.m_vertexes);
		m_indexes = std::move(_right.m_indexes);
		return *this;
	}



	auto basic_mesh::setVertexes(vertex_storage _vertexes) noexcept -> void
	{
		m_vertexes = std::move(_vertexes);
	}



	auto basic_mesh::getVertexes() const noexcept -> const vertex_storage&
	{
		return m_vertexes;
	}



	auto basic_mesh::setIndexes(index_storage _indexes) noexcept -> void
	{
		m_indexes = std::move(_indexes);
	}



	auto basic_mesh::getIndexes() const noexcept -> const index_storage&
	{
		return m_indexes;
	}



	auto basic_mesh::getIndexesCount() const noexcept -> size_t
	{
		return m_indexes.size();
	}



	auto basic_mesh::getVetexesCount() const noexcept -> size_t
	{
		return m_vertexes.size();
	}
}