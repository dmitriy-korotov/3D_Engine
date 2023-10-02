#include <engine/ecs/systems/move_camera_system.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/entities/entities_manager.hpp>

#include <engine/ecs/components/active_camera_component.hpp>
#include <engine/ecs/components/camera_transform_component.hpp>
#include <engine/ecs/components/move_camera_component.hpp>
#include <engine/ecs/components/vision_component.hpp>

#include <engine/input/keyboard.hpp>

#include <engine/application_settings.hpp>



using namespace engine::ecs::components;
using namespace engine::input;



namespace engine::ecs::systems
{
	void move_camera_system::update(float _delta_time) const noexcept
	{
		auto active_camera_components = ECS::instance().getComponentsManager()->getComponents<active_camera_component>();
		if (active_camera_components.has_value())
		{
			auto& begin = active_camera_components->first;
			auto& end = active_camera_components->second;

			for (; begin != end; begin++)
			{
				const auto& owner = ECS::instance().getEntitiesManager()->getEntity(begin->getOwner());

				auto& opt_transform_component = owner->getComponent<camera_transform_component>();
				auto& opt_move_component = owner->getComponent<move_camera_component>();
				auto& opt_vision_component = owner->getComponent<vision_component>();

				if (!opt_transform_component.has_value() || !opt_move_component.has_value() || !opt_vision_component.has_value())
				{
					continue;
				}

				auto& transform_component = opt_transform_component.value().lock();
				auto& move_component = opt_move_component.value().lock();
				auto& vision_component = opt_vision_component.value().lock();



				glm::vec3 movement_delta(0.f);

				glm::vec3 velocity = move_component->getVelocity();

				if (keyboard::isKeyPressed(engine::input::Key::KEY_LEFT_SHIFT))
				{
					velocity *= 5.f;
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_LEFT_CONTROL))
				{
					velocity /= 5.f;
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_W))
				{
					transform_component->moveForward(velocity.x * _delta_time);
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_S))
				{
					transform_component->moveForward(-velocity.x * _delta_time);
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_D))
				{
					transform_component->moveRight(velocity.y * _delta_time);
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_A))
				{
					transform_component->moveRight(-velocity.y * _delta_time);
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_E))
				{
					transform_component->moveUp(velocity.z * _delta_time);
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_Q))
				{
					transform_component->moveUp(-velocity.z * _delta_time);
				}



				glm::vec3 rotation_delta(0.f);

				if (keyboard::isKeyPressed(engine::input::Key::KEY_UP))
				{
					rotation_delta.y -= 0.1f;
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_DOWN))
				{
					rotation_delta.y += 0.1f;
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_RIGHT))
				{
					rotation_delta.z -= 0.1f;
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_LEFT))
				{
					rotation_delta.z += 0.1f;
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_KP_6))
				{
					rotation_delta.x -= 0.1f;
				}
				if (keyboard::isKeyPressed(engine::input::Key::KEY_KP_4))
				{
					rotation_delta.x += 0.1f;
				}



				transform_component->setRotation(transform_component->getRotation() + rotation_delta);

				vision_component->setViewPortSize(application_settings::instance().getWidth(), application_settings::instance().getHeight());
			}
		}
	}
}