#pragma once

#include <engine/render/basic_mesh.hpp>

#include <engine/interfaces/usage_object.hpp>

#include <engine/render/open_gl/vertex_buffer.hpp>
#include <engine/render/open_gl/index_buffer.hpp>
#include <engine/render/open_gl/vertex_array.hpp>

#include <memory>



namespace engine::render::open_gl
{
	class mesh final: public basic_mesh 
	{
	public:

		mesh(vertex_storage _vertexes, index_storage _indexes) noexcept;
		mesh(mesh&& _other) noexcept;
		mesh& operator=(mesh&& _right) noexcept;

		void use() const noexcept override;
		void unuse() const noexcept override;

		void swap(mesh& _other) noexcept;

	public:

		vertex_buffer m_VBO;
		index_buffer m_EBO;
		vertex_array m_VAO;

	};
}