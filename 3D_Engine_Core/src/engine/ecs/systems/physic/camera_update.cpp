#include <engine/ecs/systems/physic/camera_update.hpp>

#include <engine/logging/log.hpp>

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/components/markers.hpp>
#include <engine/ecs/components/physic.hpp>

#include <engine/input/keyboard.hpp>
#include <engine/input/mouse.hpp>

#include <engine/modules/ui/application_UIModule.hpp>

#include <engine/application_settings.hpp>



using namespace engine::ecs::components;
using namespace engine::input;
using namespace engine::modules::ui;

namespace engine::ecs::systems
{
	void camera_update::update(float _delta_time) const noexcept
	{
		auto active_camera_components = ECS::instance().getComponentsManager()->getComponents<active_camera>();
		if (active_camera_components.has_value())
		{
			const auto& active_camera_comp = active_camera_components->first;

			const auto& active_camera_ent = ECS::instance().getEntitiesManager()->getEntity(active_camera_comp->getOwner());

			auto& opt_transform_comp = active_camera_ent->getComponent<camera_transform>();
			auto& opt_move_comp = active_camera_ent->getComponent<velocity>();
			auto& opt_vision_comp = active_camera_ent->getComponent<vision>();

			if (!opt_transform_comp.has_value() || !opt_move_comp.has_value() || !opt_vision_comp.has_value())
			{
				LOG_ERROR("[Move camera system ERROR] Active camera is not have heeded components");
				return;
			}

			auto& transform_comp = opt_transform_comp.value().lock();
			auto& move_comp = opt_move_comp.value().lock();
			auto& vision_comp = opt_vision_comp.value().lock();



			translateCamera(*transform_comp, *move_comp, _delta_time);
			rotateCamera(*transform_comp, *move_comp, _delta_time);



			vision_comp->setViewPortSize(application_settings::instance().getWidth(), application_settings::instance().getHeight());
		}
	}



	void camera_update::translateCamera(camera_transform& _transform_component,
										velocity& _move_component, float _delta_time) const noexcept
	{
		glm::vec3 movement_delta(0.f);

		glm::vec3 velocity = _move_component.getVelocity();

		if (keyboard::isKeyPressed(Key::KEY_LEFT_SHIFT))
		{
			velocity *= 5.f;
		}
		if (keyboard::isKeyPressed(Key::KEY_LEFT_CONTROL))
		{
			velocity /= 5.f;
		}
		if (keyboard::isKeyPressed(Key::KEY_W))
		{
			_transform_component.moveForward(velocity.x * _delta_time);
		}
		if (keyboard::isKeyPressed(Key::KEY_S))
		{
			_transform_component.moveForward(-velocity.x * _delta_time);
		}
		if (keyboard::isKeyPressed(Key::KEY_D))
		{
			_transform_component.moveRight(velocity.y * _delta_time);
		}
		if (keyboard::isKeyPressed(Key::KEY_A))
		{
			_transform_component.moveRight(-velocity.y * _delta_time);
		}
		if (keyboard::isKeyPressed(Key::KEY_E))
		{
			_transform_component.moveUp(velocity.z * _delta_time);
		}
		if (keyboard::isKeyPressed(Key::KEY_Q))
		{
			_transform_component.moveUp(-velocity.z * _delta_time);
		}
	}



	void camera_update::rotateCamera(camera_transform& _transform_component,
									 velocity& _move_component, float _delta_time) const noexcept
	{
		glm::vec3 rotation_delta(0.f);

		if (keyboard::isKeyPressed(Key::KEY_UP))
		{
			rotation_delta.y -= 0.1f;
		}
		if (keyboard::isKeyPressed(Key::KEY_DOWN))
		{
			rotation_delta.y += 0.1f;
		}
		if (keyboard::isKeyPressed(Key::KEY_RIGHT))
		{
			rotation_delta.z -= 0.1f;
		}
		if (keyboard::isKeyPressed(Key::KEY_LEFT))
		{
			rotation_delta.z += 0.1f;
		}
		if (keyboard::isKeyPressed(Key::KEY_KP_6))
		{
			rotation_delta.x -= 0.1f;
		}
		if (keyboard::isKeyPressed(Key::KEY_KP_4))
		{
			rotation_delta.x += 0.1f;
		}

		auto current_mouse_position = glm::dvec2(mouse::getCursorPositionX(), mouse::getCursorPositionY());

		auto& UI_module = application_UIModule::instance().getUIModule();
		if (!UI_module->isInitialized() || (UI_module->isInitialized() && !UI_module->isMouseOnUI()))
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