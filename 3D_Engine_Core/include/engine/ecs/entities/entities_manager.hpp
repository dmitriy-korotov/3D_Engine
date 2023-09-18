#pragma once

#include <engine/ecs/ecs.hpp>

#include <unordered_map>
#include <memory>



namespace engine::ecs::entities
{
	class basic_entity;

	class entities_manager
	{
	public:

		using entity_ptr = std::shared_ptr<basic_entity>;
		using entities_storage = std::unordered_map<entity_id, entity_ptr>;

		entities_manager() = default;
		~entities_manager();

		template <typename EntityType, typename ...Args>
		entity_id createEntity(Args&&... _args);

		void destroyEntity(entity_id _entity_id) noexcept;

		void destroyAllEntities() noexcept;

		entity_ptr getEntity(entity_id _entity_id) const noexcept;

	private:

		entities_storage m_entities;

	};





	template <typename EntityType, typename ...Args>
	entity_id entities_manager::createEntity(Args&&... _args)
	{
		static_assert(std::is_base_of_v<basic_entity, EntityType>, "EntityType is not derived basic_entity");

		auto entity_ptr = std::make_shared<EntityType>(std::forward<Args>(_args)...);
		entity_id id = entity_ptr->getID();
		m_entities.emplace(id, std::move(entity_ptr));

		return id;
	}
}