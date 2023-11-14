#include <engine/scene/renderable_scene_object.hpp>

#include <engine/logging/log.hpp>

#include <engine/ecs/components/render.hpp>
#include <engine/ecs/components/physic/transform.hpp>

#include <engine/resource_manager.hpp>





using namespace engine::ecs::components;

namespace engine::scene
{
	renderable_scene_object::renderable_scene_object(std::string_view _model_name, std::string_view _program_name) noexcept
	{
		addComponent<transform>();
		
		auto model = GetResourceManager().getModel(_model_name);
		if (model == nullptr)
		{
			LOG_ERROR("[Renderable scene object ERROR] Model with name '{0}' not found", _model_name);
			return;
		}

		addComponent<mesh>(model->getMeshes());
		
		if (model->hasMaterial())
			addComponent<ecs::components::material>(model->getMaterial());
		else
			addComponent<color>(glm::vec4(0.3f, 0.3f, 0.3f, 1.f));

		

		auto shader_program = GetResourceManager().getShaderProgram(_program_name);
		if (shader_program == nullptr)
		{
			LOG_ERROR("[Renderable scene object ERROR] Shader program with name '{0}' not found", _model_name);
			return;
		}

		addComponent<renderable>(std::move(shader_program));
	}
}