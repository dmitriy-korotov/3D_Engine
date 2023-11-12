#include <engine/ecs/components/render/light/point_light.hpp>

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/components/components_manager.hpp>

#include <engine/ecs/components/physic/position.hpp>

#include <engine/Engine.hpp>



namespace engine::ecs::components
{
	glm::vec3 point_light::getPosition() const noexcept
	{
		auto position_comp = ECS::instance().getComponentsManager()->getComponent<position>(getOwner());
		if (position_comp == nullptr)
		{
			LOG_ERROR("[Point light component ERROR] Entity hasn't 'position' component");
			return glm::vec3(0.f);
		}
		return position_comp->getPosition();
	}



	bool point_light::putOnUI() noexcept
	{
		bool is_clicked = false;

		is_clicked |= light::putOnUI();
		is_clicked |= light_attenuation::putOnUI();

		return is_clicked;
	}
}