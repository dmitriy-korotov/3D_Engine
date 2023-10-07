#include <engine/scene/renderable_scene_object.hpp>

#include <engine/ecs/components/render.hpp>
#include <engine/ecs/components/physic/rotation.hpp>
#include <engine/ecs/components/physic/scale.hpp>

//#include <engine/render/model.hpp>



using namespace engine::ecs::components;

namespace engine::scene
{
	renderable_scene_object::renderable_scene_object(const std::string_view& _path_to_model, shader_program_ptr _shader_program) noexcept
	{
		addComponent<rotation>();
		addComponent<scale>();
		
		addComponent<mesh>();
		addComponent<material>();
		if (_shader_program != nullptr)
		{
			addComponent<renderable>(std::move(_shader_program));
		}
	}
}