#include <engine/render/meshes/open_gl/mesh.hpp>

#include <engine/render/open_gl/buffer_layout.hpp>



namespace engine::render::meshes::open_gl
{
	mesh::mesh(vertex_storage _vertexes, index_storage _indexes) noexcept
			: basic_mesh(std::move(_vertexes))
			, m_indexes(std::move(_indexes))
			, m_VBO(m_vertexes.data(), sizeof(vertex_storage::value_type)* m_vertexes.size(),
					{ ShaderDataType::Float3,
					  ShaderDataType::Float3,
					  ShaderDataType::Float2 }, vertex_buffer::Usage::Static)
			, m_EBO(m_indexes.data(), sizeof(index_storage::value_type) * m_indexes.size(), vertex_buffer::Usage::Static)
	{
		m_VAO.addVertexBuffer(m_VBO);
		m_VAO.setIndexBuffer(m_EBO);
	}



	const mesh::index_storage& mesh::getIndexes() const noexcept
	{
		return m_indexes;
	}



	void mesh::use() const noexcept
	{
		m_VAO.bind();
	}



	void mesh::unuse() const noexcept
	{
		m_VAO.unbind();
	}
}