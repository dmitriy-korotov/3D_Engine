#pragma once

#include <engine/util/nocopyeble.hpp>
#include <engine/interfaces/usage_object.hpp>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>



namespace engine::render
{
	struct vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 tex_coord;
	};

	class basic_mesh : private util::nocopyeble, public interfaces::usage_object
	{
	public:

		using vertex_storage = std::vector<vertex>;
		using index_storage = std::vector<unsigned int>;

		basic_mesh() = default;
		basic_mesh(vertex_storage _vertexes, index_storage _indexes) noexcept;
		basic_mesh(basic_mesh&& _other) noexcept;
		basic_mesh& operator=(basic_mesh&& _right) noexcept;
		virtual ~basic_mesh() = default;

		void setVertexes(vertex_storage _vertexes) noexcept;
		const vertex_storage& getVertexes() const noexcept;
		void setIndexes(index_storage _indexes) noexcept;
		const index_storage& getIndexes() const noexcept;

		size_t getIndexesCount() const noexcept;
		size_t getVetexesCount() const noexcept;

	protected:

		vertex_storage m_vertexes;
		index_storage m_indexes;

	};
}