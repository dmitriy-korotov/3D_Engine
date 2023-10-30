#pragma once

#include <engine/render/shaders_manager.hpp>



namespace engine
{
	class resource_manager: public render::shaders_manager
	{
	private:

		friend resource_manager& GetResourceManager() noexcept;

		static resource_manager& instance() noexcept;

	};



	resource_manager& GetResourceManager() noexcept;
}