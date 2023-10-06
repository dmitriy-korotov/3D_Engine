#include <engine/ecs/systems/move_camera_system.hpp>

#include <engine/logging/log.hpp>

#include <engine/ecs/ecs_system.hpp>

#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/entities/entities_manager.hpp>

#include <engine/ecs/components/markers/active_camera.hpp>
#include <engine/ecs/components/render/transform_camera_component.hpp>
#include <engine/ecs/components/render/vision_component.hpp>
#include <engine/ecs/components/physic/velocity.hpp>

#include <engine/input/keyboard.hpp>
#include <engine/input/mouse.hpp>
#include <engine/modules/imgui/UIModule.hpp>

#include <engine/application_settings.hpp>



using namespace engine::ecs::components;
using namespace engine::input;



namespace engine::ecs::systems
{
	void move_camera_system::update(float _delta_time) const noexcept
	{
		auto active_camera_components = ECS::instance().getComponentsManager()->getComponents<active_camera>();
		if (active_camera_components.has_value())
		{
			auto& begin = active_camera_components->first;

			const auto& owner = ECS::instance().getEntitiesManager()->getEntity(begin->getOwner());

			auto& opt_transform_component = owner->getComponent<transform_camera_component>();
			auto& opt_move_component = owner->getComponent<velocity>();
			auto& opt_vision_component = owner->getComponent<vision_component>();

			if (!opt_transform_component.has_value() || !opt_move_component.has_value() || !opt_vision_component.has_value())
			{
				LOG_ERROR("[Move camera system ERROR] Active camera is not have heeded components");
				return;
			}

			auto& transform_component = opt_transform_component.value().lock();
			auto& move_component = opt_move_component.value().lock();
			auto& vision_component = opt_vision_component.value().lock();



			translateCamera(*transform_component, *move_component, _delta_time);
			rotateCamera(*transform_component, *move_component, _delta_time);



			vision_component->setViewPortSize(application_settings::instance().getWidth(), application_settings::instance().getHeight());
		}
	}



	void move_camera_system::translateCamera(transform_camera_component& _transform_component,
											 velocity& _move_component, float _delta_time) const noexcept
	{
		glm::vec3 movement_delta(0.f);

		glm::vec3 velocity = _move_component.getVelocity();

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
			_transform_component.moveForward(velocity.x * _delta_time);
		}
		if (keyboard::isKeyPressed(engine::input::Key::KEY_S))
		{
			_transform_component.moveForward(-velocity.x * _delta_time);
		}
		if (keyboard::isKeyPressed(engine::input::Key::KEY_D))
		{
			_transform_component.moveRight(velocity.y * _delta_time);
		}
		if (keyboard::isKeyPressed(engine::input::Key::KEY_A))
		{
			_transform_component.moveRight(-velocity.y * _delta_time);
		}
		if (keyboard::isKeyPressed(engine::input::Key::KEY_E))
		{
			_transform_component.moveUp(velocity.z * _delta_time);
		}
		if (keyboard::isKeyPressed(engine::input::Key::KEY_Q))
		{
			_transform_component.moveUp(-velocity.z * _delta_time);
		}
	}



	void move_camera_system::rotateCamera(transform_camera_component& _transform_component,
										  velocity& _move_component, float _delta_time) const noexcept
	{
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

		auto current_mouse_position = glm::dvec2(mouse::getCursorPositionX(), mouse::getCursorPositionY());

		if (!modules::imgui::UIModule::instance().isMouseOnUI())
		{
			if (mouse::isButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
			{
				rotation_delta.z -= (current_mouse_position.x - m_last_cursor_position.x) / 10;
				rotation_delta.y += (current_mouse_position.y - m_last_cursor_position.y) / 10;
			}
			if (mouse::isButtonPressed(MouseButton::MOUSE_BUTTON_RIGHT))
			{
				_transform_component.moveRight((current_mouse_position.x - m_last_cursor_position.x) / 100);
				_transform_component.moveWorldUp((current_mouse_position.y - m_last_cursor_position.y) / 100);
			}
		}
		
		m_last_cursor_position = current_mouse_position;

		_transform_component.setRotation(_transform_component.getRotation() + rotation_delta);
	}
}