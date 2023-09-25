#pragma once

#include <glm/vec3.hpp>

#include <vector>



namespace engine::meshes
{
	class basic_mesh
	{
	public:

		using vectors_storage = std::vector<glm::vec3>;

		basic_mesh(vectors_storage _vertex_positions, vectors_storage _vertex_normals, vectors_storage _vertex_tex_coords) noexcept;
		virtual ~basic_mesh() = default;



	protected:

		vectors_storage m_vertex_positions;
		vectors_storage m_vertex_normals;
		vectors_storage m_vertex_tex_coords;

	};
}