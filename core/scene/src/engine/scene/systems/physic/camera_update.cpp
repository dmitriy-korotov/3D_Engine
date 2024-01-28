#include <engine/scene/systems/physic/camera_update.hpp>

#include <engine/logging/log.hpp>

#include <engine/scene/Scene.hpp>

#include <engine/scene/components/markers.hpp>
#include <engine/scene/components/physic.hpp>

#include <engine/input/keyboard.hpp>
#include <engine/input/mouse.hpp>

#include <engine/Engine.hpp>

#include <engine/application_settings.hpp>





using namespace engine::input;
using namespace engine::modules::ui;

namespace engine::scene::systems
{
	auto camera_update::update(float _delta_time) noexcept -> void
	{
		auto active_camera_component = Scene::getComponent<active_camera>();
		if (active_camera_component != nullptr)
		{
			const auto& active_camera_ent = Scene::getObject(active_camera_component->getOwner());

			const auto& vision_comp = active_camera_ent->getComponent<vision>();
			if (vision_comp == nullptr)
			{
				LOG_ERROR("[Camera update system ERROR] Active camera is not have 'vision' component");
				return;
			}
			vision_comp->setViewPortSize(application_settings::instance().getWidth(),
										 application_settings::instance().getHeight());



			const auto& movement_comp = active_camera_ent->getComponent<movement>();
			const auto& movement_velocity_comp = active_camera_ent->getComponent<movement_velocity>();
			
			if (movement_comp == nullptr || movement_velocity_comp == nullptr)
				LOG_WARN("[Camera update system WARN] Active camera is not have movement components");
			else
				moveCamera(*movement_comp, *movement_velocity_comp, _delta_time);



			const auto& rotate_comp = active_camera_ent->getComponent<rotate>();
			const auto& rotate_velocity_comp = active_camera_ent->getComponent<rotate_velocity>();

			if (rotate_comp == nullptr || rotate_velocity_comp == nullptr)
				LOG_WARN("[Camera update system WARN] Active camera is not have rotate components");
			else
				rotateCamera(*rotate_comp, *rotate_velocity_comp, _delta_time);
		}
	}



	auto camera_update::moveCamera(const movement& _movement_component,
								   const movement_velocity& _movement_velocity_component, float _delta_time) const noexcept -> void
	{
		glm::vec3 velocity = _movement_velocity_component.getVelocity();

		if (keyboard::isKeyPressed(Key::KEY_LEFT_SHIFT))
			velocity *= 5.f;

		if (keyboard::isKeyPressed(Key::KEY_LEFT_CONTROL))
			velocity /= 5.f;
		
		if (keyboard::isKeyPressed(Key::KEY_W))
			_movement_component.moveForward(velocity.x * _delta_time);
		
		if (keyboard::isKeyPressed(Key::KEY_S))
			_movement_component.moveForward(-velocity.x * _delta_time);
		
		if (keyboard::isKeyPressed(Key::KEY_D))
			_movement_component.moveRight(velocity.y * _delta_time);
		
		if (keyboard::isKeyPressed(Key::KEY_A))
			_movement_component.moveRight(-velocity.y * _delta_time);
		
		if (keyboard::isKeyPressed(Key::KEY_E))
			_movement_component.moveUp(velocity.z * _delta_time);
		
		if (keyboard::isKeyPressed(Key::KEY_Q))
			_movement_component.moveUp(-velocity.z * _delta_time);



		auto current_mouse_position = glm::dvec2(mouse::getCursorPositionX(), mouse::getCursorPositionY());

		auto& UI_module = Engine::getApplicationUIModule();
		if (!UI_module->isInitialized() || (UI_module->isInitialized() && !UI_module->isMouseOnUI()))
		{
			if (mouse::isButtonPressed(MouseButton::MOUSE_BUTTON_RIGHT))
			{
				double dx = (current_mouse_position.x - m_last_cursor_position.x) / 5.f;
				double dy = (current_mouse_position.y - m_last_cursor_position.y) / 5.f;

				_movement_component.moveRight(dx * velocity.y * _delta_time);
				_movement_component.moveWorldUp(-dy * velocity.z * _delta_time);
			}
		}
	}



	auto camera_update::rotateCamera(const rotate& _rotate_component,
									 const rotate_velocity& _rotate_velocity_component, float _delta_time) noexcept -> void
	{
		glm::vec3 rotation_delta(0.f);

		if (keyboard::isKeyPressed(Key::KEY_UP))
			_rotate_component.rotateY(_rotate_velocity_component.getVelocity().y * _delta_time);
		
		if (keyboard::isKeyPressed(Key::KEY_DOWN))
			_rotate_component.rotateY(-_rotate_velocity_component.getVelocity().y * _delta_time);
		
		if (keyboard::isKeyPressed(Key::KEY_RIGHT))
			_rotate_component.rotateZ(_rotate_velocity_component.getVelocity().z * _delta_time);
		
		if (keyboard::isKeyPressed(Key::KEY_LEFT))
			_rotate_component.rotateZ(-_rotate_velocity_component.getVelocity().z * _delta_time);
		
		if (keyboard::isKeyPressed(Key::KEY_KP_6))
			_rotate_component.rotateX(-_rotate_velocity_component.getVelocity().x * _delta_time);

		if (keyboard::isKeyPressed(Key::KEY_KP_4))
			_rotate_component.rotateX(_rotate_velocity_component.getVelocity().x * _delta_time);



		auto current_mouse_position = glm::dvec2(mouse::getCursorPositionX(), mouse::getCursorPositionY());

		auto& UI_module = Engine::getApplicationUIModule();
		if (!UI_module->isInitialized() || (UI_module->isInitialized() && !UI_module->isMouseOnUI()))
		{
			if (mouse::isButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
			{
				double dx = (current_mouse_position.x - m_last_cursor_position.x) / 5.f;
				double dy = (current_mouse_position.y - m_last_cursor_position.y) / 5.f;

				_rotate_component.rotateZ(dx * _delta_time * _rotate_velocity_component.getVelocity().z);
				_rotate_component.rotateY(-dy * _delta_time * _rotate_velocity_component.getVelocity().y);
			}
		}
		m_last_cursor_position = current_mouse_position;
	}





	auto camera_update::serialize() const -> serialized_view_t
	{
		serialized_view_t serialized_view = scene_system::serialize();

		serialized_view["system_name"] = system_name;

		return serialized_view;
	}
}