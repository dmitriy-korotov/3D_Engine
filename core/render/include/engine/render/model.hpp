#pragma once

#include <engine/render/fwd/basic_mesh.hpp>
#include <engine/render/fwd/material.hpp>

#include <vector>
#include <memory>



namespace engine::render
{
	class model
	{
	public:

		using meshes_storage_t = std::vector<std::shared_ptr<basic_mesh>>;
		using material_ptr_t = std::shared_ptr<material>;

		model() = default;
		model(meshes_storage_t&& _meshes, material_ptr_t _material) noexcept;

		void setMeeshes(meshes_storage_t&& _meshes) noexcept;
		void setMaterial(material_ptr_t _material) noexcept;

		const meshes_storage_t& getMeshes() const & noexcept;
		meshes_storage_t&& getMeshes() && noexcept;
		material_ptr_t&& getMaterial() && noexcept;
		const material_ptr_t& getMaterial() const & noexcept;

		bool hasMaterial() const noexcept;

	private:

		meshes_storage_t m_meshes;
		material_ptr_t m_material = nullptr;

	};
}