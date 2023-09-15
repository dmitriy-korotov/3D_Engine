#pragma once

#include <engine/ecs/ecs.hpp>

#include <vector>
#include <memory>



namespace engine::ecs::entities
{
	class basic_entity;

	class entities_manager
	{
	public:

		using entity_ptr = std::shared_ptr<basic_entity>;
		using entities_storage = std::vector<entity_ptr>;

		~entities_manager();

		template <typename EntityType, typename ...Args>
		void createEntity(Args&&... _args);

		void destroyEntity(entity_id _entity_id) noexcept;

		void destroyAllEntities() noexcept;

	private:

		entities_storage m_entities;

	};





	template <typename EntityType, typename ...Args>
	void entities_manager::createEntity(Args&&... _args)
	{
		static_assert(std::is_base_of_v <basic_entity, EntityType> "EntityType is not derived basic_entity");

		m_entities.push_back(std::make_shared<EntityType>(std::forward<Args>(_args)...));
	}
}