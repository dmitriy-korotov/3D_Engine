#pragma once

#include <engine/ecs/ecs_system.hpp>
#include <engine/ecs/entities/entities_manager.hpp>
#include <engine/ecs/components/components_manager.hpp>
#include <engine/ecs/entities/basic_entity.hpp>

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>



namespace engine::ecs::components
{
	class components_creator
	{
	public:

		using creatorfn_t = std::function<std::shared_ptr<basic_component>(entities::entity_id_t)>;
		using creatorfn_ptr_t = std::shared_ptr<creatorfn_t>;
		using creators_map_t = std::unordered_map<std::string, creatorfn_ptr_t>;

		static bool addComponentCreator(std::string _creator_name, creatorfn_t _creator) noexcept;

		static [[nodiscard]] creatorfn_ptr_t getComponentCreator(const std::string& _creator_name) noexcept;

	private:

		static creators_map_t m_creators;

	};



	template <typename ComponentType>
	void AddComponentCreator() noexcept
	{
		//static_cast(std::is_base_of_v<basic_component, ComponentType>, "")

		components_creator::addComponentCreator(std::string(ComponentType::component_name),
			[](entities::entity_id_t _target) -> components_manager::component_ptr_t<basic_component>
			{
				auto entity = ECS::instance().getEntitiesManager()->getEntity(_target);
				entity->addComponent<ComponentType>();
				return entity->getComponent<ComponentType>();
			});
	}
}