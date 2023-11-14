#include <engine/render/model.hpp>



namespace engine::render
{
	model::model(meshes_storage_t&& _meshes, material_ptr_t _material) noexcept
			: m_meshes(std::move(_meshes))
			, m_material(std::move(_material))
	{ }



	auto model::setMeeshes(meshes_storage_t&& _meshes) noexcept -> void
	{
		m_meshes = std::move(_meshes);
	}



	auto model::setMaterial(material_ptr_t _material) noexcept -> void
	{
		m_material = std::move(_material);
	}



	auto model::getMeshes() const& noexcept -> const meshes_storage_t&
	{
		return m_meshes;
	}



	auto model::getMeshes() && noexcept -> meshes_storage_t&&
	{
		return std::move(m_meshes);
	}



	auto model::getMaterial() && noexcept -> material_ptr_t&&
	{
		return std::move(m_material);
	}



	auto model::getMaterial() const& noexcept -> const material_ptr_t&
	{
		return m_material;
	}
}