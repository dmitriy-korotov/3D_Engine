#include <engine/resource_manager.hpp>



namespace engine
{
	auto resource_manager::instance() noexcept -> resource_manager&
	{
		static resource_manager instance;
		return instance;
	}



	auto resource_manager::getShadersManager() const noexcept -> render::shaders_manager&
	{
		return render::shaders_manager::instance();
	}



	auto resource_manager::getModelsManager() const noexcept -> render::models_manager&
	{
		return render::models_manager::instance();
	}





	auto GetResourceManager() noexcept -> resource_manager&
	{
		return resource_manager::instance();
	}
}