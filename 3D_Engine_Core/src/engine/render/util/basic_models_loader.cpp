#include <engine/render/util/basic_models_loader.hpp>



namespace engine::render::utility
{
	auto basic_models_loader::getMeshes() && noexcept -> mesh_storage&&
	{
		return std::move(m_meshes);
	}



	auto basic_models_loader::getMaterial() && noexcept -> material_ptr&&
	{
		return std::move(m_material);
	}



	auto basic_models_loader::isLoaded() const noexcept -> bool
	{
		return m_is_loaded;
	}



	auto basic_models_loader::hasMaterial() const noexcept -> bool
	{
		return m_material != nullptr;
	}
}