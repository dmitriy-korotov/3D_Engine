#include <engine/render/util/basic_models_loader.hpp>



namespace engine::render::utility
{
	basic_models_loader::mesh_storage& basic_models_loader::getMeshes() noexcept
	{
		return m_meshes;
	}



	basic_models_loader::material_ptr& basic_models_loader::getMaterial() noexcept
	{
		return m_material;
	}



	bool basic_models_loader::isLoaded() const noexcept
	{
		return m_is_loaded;
	}



	bool basic_models_loader::hasMaterial() const noexcept
	{
		return m_material != nullptr;
	}
}