#include <engine/render/open_gl/mesh.hpp>

#include <engine/render/open_gl/buffer_layout.hpp>



namespace engine::render::open_gl
{
	mesh::mesh(vertex_storage _vertexes, index_storage _indexes) noexcept
			: basic_mesh(std::move(_vertexes), std::move(_indexes))
			, m_VBO(m_vertexes.data(), sizeof(vertex_storage::value_type) * m_vertexes.size(),
					{ ShaderDataType::Float3,
					  ShaderDataType::Float3,
					  ShaderDataType::Float2 }, vertex_buffer::Usage::Static)
			, m_EBO(m_indexes.data(), m_indexes.size(), index_buffer::Usage::Static)
	{
		m_VAO.addVertexBuffer(m_VBO);
		m_VAO.setIndexBuffer(m_EBO);
	}



	mesh::mesh(mesh&& _other) noexcept
			: basic_mesh(std::move(_other))
			, m_EBO(std::move(_other.m_EBO))
			, m_VBO(std::move(_other.m_VBO))
			, m_VAO(std::move(_other.m_VAO))
	{ }



	auto mesh::operator=(mesh&& _right) noexcept -> mesh&
	{
		mesh tmp = std::move(_right);
		swap(tmp);
		return *this;
	}



	auto mesh::swap(mesh& _other) noexcept -> void
	{
		std::swap(m_vertexes, _other.m_vertexes);
		std::swap(m_indexes, _other.m_indexes);
		std::swap(m_VBO, _other.m_VBO);
		std::swap(m_EBO, _other.m_EBO);
		std::swap(m_VAO, _other.m_VAO);
	}



	auto mesh::use() const noexcept -> void
	{
		m_VAO.bind();
	}



	auto mesh::unuse() const noexcept -> void
	{
		m_VAO.unbind();
	}
}