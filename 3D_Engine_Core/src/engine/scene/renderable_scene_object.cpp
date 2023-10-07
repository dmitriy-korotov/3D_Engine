#include <engine/scene/renderable_scene_object.hpp>

#include <engine/logging/log.hpp>

#include <engine/ecs/components/render.hpp>
#include <engine/ecs/components/physic/rotation.hpp>
#include <engine/ecs/components/physic/scale.hpp>

#include <engine/render/util/models_loader.hpp>



using namespace engine::ecs::components;
using namespace engine::render::utility;

namespace engine::scene
{
	renderable_scene_object::renderable_scene_object(const std::string_view& _path_to_model, shader_program_ptr _shader_program) noexcept
	{
		addComponent<rotation>();
		addComponent<scale>();
		
		models_loader loader;
		loader.load(_path_to_model);
		if (!loader.isLoaded())
		{
			LOG_ERROR("[Renderable scene object ERROR] Can't load model (path: {0})", _path_to_model);
			return;
		}

		addComponent<mesh>(std::move(loader.getMeshes()));
		addComponent<material>(std::move(loader.getMaterial()));

		if (_shader_program != nullptr)
		{
			addComponent<renderable>(std::move(_shader_program));
		}
	}
}