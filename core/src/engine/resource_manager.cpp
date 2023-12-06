#include <engine/resource_manager.hpp>



namespace engine
{
	auto resource_manager::instance() noexcept -> resource_manager&
	{
		static resource_manager instance;
		return instance;
	}





	auto GetResourceManager() noexcept -> resource_manager&
	{
		return resource_manager::instance();
	}
}