#pragma once

#include <engine/render/shaders_manager.hpp>
#include <engine/render/models_manager.hpp>



namespace engine
{
	class resource_manager: public render::shaders_manager,
							public render::models_manager
	{
	private:

		friend resource_manager& GetResourceManager() noexcept;

		static resource_manager& instance() noexcept;

	};



	resource_manager& GetResourceManager() noexcept;
}