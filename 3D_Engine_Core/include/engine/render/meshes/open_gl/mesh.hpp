#pragma once

#include <engine/render/meshes/basic_mesh.hpp>

#include <engine/interfaces/usage_object.hpp>

#include <engine/render/open_gl/vertex_buffer.hpp>
#include <engine/render/open_gl/index_buffer.hpp>
#include <engine/render/open_gl/vertex_array.hpp>

#include <memory>



namespace engine::render::meshes::open_gl
{
	using namespace render::open_gl;

	class mesh final : public basic_mesh, public interfaces::usage_object  
	{
	public:

		using index_storage = std::vector<unsigned int>;

		mesh(vertex_storage _vertexes, index_storage _indexes) noexcept;

		const index_storage& getIndexes() const noexcept;

		void use() const noexcept override;
		void unuse() const noexcept override;

	private:

		index_storage m_indexes;

		vertex_buffer m_VBO;
		index_buffer m_EBO;
		vertex_array m_VAO;

	};
}