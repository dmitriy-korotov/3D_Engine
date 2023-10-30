#include <engine/resource_manager.hpp>



namespace engine
{
	resource_manager& resource_manager::instance() noexcept
	{
		static resource_manager instance;
		return instance;
	}





	resource_manager& GetResourceManager() noexcept
	{
		return resource_manager::instance();
	}
}