#pragma once

#include <engine/util/nocopyeble.hpp>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>



namespace engine::render::meshes
{
	struct vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 tex_coord;
	};

	class basic_mesh : private util::nocopyeble
	{
	public:

		using vertex_storage = std::vector<vertex>;

		basic_mesh(vertex_storage _vertexes) noexcept;
		virtual ~basic_mesh() = default;

		void setVertexes(vertex_storage _vertexes) noexcept;
		const vertex_storage& getVertexes() const noexcept;

	protected:

		vertex_storage m_vertexes;

	};
}