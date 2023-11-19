#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/ecs.hpp>

#include <engine/ecs/entities/basic_entity.hpp>

#include <unordered_map>
#include <memory>
#include <concepts>



namespace engine::ecs::entities
{
	template <Entity UserBasicEntity>
	class entities_manager: util::nocopyeble
	{
	public:

		using entity_ptr_t = std::shared_ptr<UserBasicEntity>;
		using entities_storage_t = std::unordered_map<entity_id_t, entity_ptr_t>;

		entities_manager() = default;
		~entities_manager();

		template <std::derived_from<UserBasicEntity> T, typename ...Args>
		[[nodiscard]] entity_ptr_t createEntity(Args&&... _args);

		bool destroyEntity(entity_id_t _entity_id) noexcept;

		void destroyAllEntities() noexcept;

		[[nodiscard]] entity_ptr_t getEntity(entity_id_t _entity_id) const noexcept;
		const entities_storage_t& getEntities() const noexcept;

	private:

		entities_storage_t m_entities;

	};





	template <Entity UserBasicEntity>
	template <std::derived_from<UserBasicEntity> T, typename ...Args>
	auto entities_manager<UserBasicEntity>::createEntity(Args&&... _args) -> entity_ptr_t
	{
		auto entity_ptr = std::make_shared<T>(std::forward<Args>(_args)...);
		entity_id_t id = entity_ptr->getID();
		auto pair = m_entities.emplace(id, entity_ptr);

		if (pair.second)
			return entity_ptr;
		
		return nullptr;
	}



	template <Entity UserBasicEntity>
	auto entities_manager<UserBasicEntity>::destroyEntity(entity_id_t _entity_id) noexcept -> bool
	{
		return m_entities.erase(_entity_id) != 0;
	}



	template <Entity UserBasicEntity>
	auto entities_manager<UserBasicEntity>::getEntity(entity_id_t _entity_id) const noexcept -> entity_ptr_t
	{
		auto entity = m_entities.find(_entity_id);

		if (entity != m_entities.end())
			return (*entity).second;
		else
			return nullptr;
	}



	template <Entity UserBasicEntity>
	auto entities_manager<UserBasicEntity>::getEntities() const noexcept -> const entities_storage_t&
	{
		return m_entities;
	}



	template <Entity UserBasicEntity>
	auto entities_manager<UserBasicEntity>::destroyAllEntities() noexcept -> void
	{
		m_entities.clear();
	}



	template <Entity UserBasicEntity>
	entities_manager<UserBasicEntity>::~entities_manager()
	{
		destroyAllEntities();
	}
}