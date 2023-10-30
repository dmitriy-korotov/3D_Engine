#include <engine/ecs/systems/render/render.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/ecs/components/render.hpp>
#include <engine/ecs/components/physic.hpp>
#include <engine/ecs/components/markers.hpp>

#include <engine/Engine.hpp>

#include <engine/render/basic_shader_program.hpp>
#include <engine/render/material.hpp>

#include <engine/application_settings.hpp>





using namespace engine::ecs::components;
using namespace engine::render;
using namespace engine::scene;

namespace engine::ecs::systems
{
	void render::preUpdate([[maybe_unused]] float _delta_time) const noexcept
	{
		auto& renderer = Engine::getApplicationRenderer();

		renderer->setViewport(application_settings::instance().getWidth(), application_settings::instance().getHeight());
		renderer->clear(Mask::ColorBuffer);
		renderer->clear(Mask::DepthBuffer);
	}




	void render::update([[maybe_unused]] float _delta_time) const noexcept
	{
		auto renderable_components = Scene::getComponents<renderable>();
		if (renderable_components.has_value())
		{
			auto& [begin, end] = renderable_components.value();

			for (;begin != end; begin++)
			{
				auto& renderable_comp = *begin;
				
				

				const auto& shader_program = renderable_comp->getShaderProgram();
				
				

				const auto& active_camera_comp = Scene::getComponent<active_camera>();
				const auto& active_camera_ent = Scene::getObject(active_camera_comp->getOwner());
				auto& camera_transform_comp = active_camera_ent->getComponent<camera_transform>();
				auto& vision_comp = active_camera_ent->getComponent<vision>();

				

				auto& current_ent = Scene::getObject(renderable_comp->getOwner());
				

				
				auto& transform_comp = current_ent->getComponent<transform>();



				shader_program->bind();
				shader_program->setMatrix4f("model_view_matrix", camera_transform_comp->getViewMatrix() * transform_comp->getModelMatrix());
				glm::mat4 mvp_matrix = vision_comp->getProjectionMatrix() * camera_transform_comp->getViewMatrix() * transform_comp->getModelMatrix();
				shader_program->setMatrix4f("mvp_matrix", mvp_matrix);
				shader_program->setMatrix3f("normal_matrix", transform_comp->getNormalMatrix());



				const auto& direction_light_comp = Scene::getComponent<direction_light>();


				
				auto material_comp = current_ent->getComponent<engine::ecs::components::material>();
				if (material_comp != nullptr && material_comp->isActive())
				{
					shader_program->setSampler2D("material.diffuse_map", *material_comp->getMaterial()->getTexture(TextureMap::Diffuse), 0);
					shader_program->setBool("material.hasDiffuseTexture", true);
				}
				else
				{
					auto color_comp = current_ent->getComponent<color>();
					if (color_comp != nullptr)
						shader_program->setVector3f("material.diffuse", color_comp->getColor());
					shader_program->setBool("material.hasDiffuseTexture", false);
				}



				auto point_light_comp = Scene::getComponent<point_light>();

				shader_program->setVector3f("scene_light.point_lights[0].position", point_light_comp->getPosition());
				shader_program->setVector3f("scene_light.point_lights[0].ambient", point_light_comp->getAmbient());
				shader_program->setVector3f("scene_light.point_lights[0].diffuse", point_light_comp->getDiffuse());
				shader_program->setVector3f("scene_light.point_lights[0].specular", point_light_comp->getSpecular());

				shader_program->setFloat("scene_light.point_lights[0].constant", point_light_comp->getConstant());
				shader_program->setFloat("scene_light.point_lights[0].linear", point_light_comp->getLinear());
				shader_program->setFloat("scene_light.point_lights[0].quadratic", point_light_comp->getQuadratic());

				shader_program->setInt("scene_light.point_lights_amount", 1);
				


				shader_program->setVector3f("light.direction", direction_light_comp->getDirection());
				shader_program->setVector3f("light.ambient", direction_light_comp->getAmbient());
				shader_program->setVector3f("light.diffuse", direction_light_comp->getDiffuse());
				shader_program->setVector3f("light.specular", direction_light_comp->getSpecular());



				auto mesh_comp = current_ent->getComponent<mesh>();
				
				


				if (mesh_comp != nullptr)
				{
					for (const auto& mesh : mesh_comp->getMeshes())
						Engine::getApplicationRenderer()->draw(*shader_program, *mesh, renderable_comp->getDrawingMode());
				}
			}
		}
	}
}