#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/render/shaders_manager.hpp>
#include <engine/render/models_manager.hpp>



namespace engine
{
	class resource_manager: util::nocopyeble
	{
	public:

		friend resource_manager& GetResourceManager() noexcept;

		render::shaders_manager& getShadersManager() const noexcept;
		render::models_manager& getModelsManager() const noexcept;

	private:

		static resource_manager& instance() noexcept;

		resource_manager() = default;

	};



	resource_manager& GetResourceManager() noexcept;
}