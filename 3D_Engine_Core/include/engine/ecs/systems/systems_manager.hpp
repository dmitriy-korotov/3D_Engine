#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/systems/basic_system.hpp>

#include <map>
#include <memory>
#include <concepts>



namespace engine::ecs::systems
{
	template <System UserBasicSystem>
	class systems_manager: private util::nocopyeble
	{
	public:

		using system_ptr_t = std::shared_ptr<UserBasicSystem>;
		using systems_storage_t = std::multimap<size_t, std::pair<std::string, system_ptr_t>>;



		systems_manager() = default;
		~systems_manager();

		void update(float _delta_time);

		template <std::derived_from<UserBasicSystem> T, typename ...Args>
		[[nodiscard]] system_ptr_t addSystem(size_t _priority, Args&&... _args) noexcept;

		const systems_storage_t& getSystems() const noexcept;

		template <std::derived_from<UserBasicSystem> T>
		bool removeSystem() noexcept;

		template <std::derived_from<UserBasicSystem> T>
		void enableSystem() noexcept;

		template <std::derived_from<UserBasicSystem> T>
		void disableSystem() noexcept;

		void removeAllSystems() noexcept;

	private:

		template <std::derived_from<UserBasicSystem> T>
		typename systems_storage_t::iterator findSystem() noexcept;

		class systems_group
		{
		public:

			systems_group(std::string _group_name, size_t _priority) noexcept;

			template <std::derived_from<UserBasicSystem> T>
			bool addSystem(system_ptr_t _system, size_t _priority_into_group) noexcept;
			
			void update(float _delta_time);

			bool operator<(const systems_group& _right) const noexcept;

		private:

			std::string m_name;
			size_t m_priority = 0;
			systems_storage_t m_systems;

		};

	private:

		systems_storage_t m_systems;

	};





	template <System UserBasicSystem>
	systems_manager<UserBasicSystem>::template systems_group::systems_group(std::string _group_name, size_t _priority) noexcept
			: m_name(std::move(_group_name))
			, m_priority(_priority)
	{ }



	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T>
	auto systems_manager<UserBasicSystem>::template systems_group::addSystem(system_ptr_t _system, size_t _priority_into_group) noexcept -> bool
	{
		auto it = m_systems.emplace(_priority_into_group, std::make_pair(T::system_name, std::move(_system)));

		return (it == m_systems.end());
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::operator<(const systems_group& _right) const noexcept -> bool
	{
		return m_priority < _right.m_priority;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::update(float _delta_time) -> void
	{
		for (const auto& system : m_systems)
		{
			if (!system.second.second->isActive())
				continue;

			system.second.second->preUpdate(_delta_time);
			system.second.second->update(_delta_time);
			system.second.second->postUpdate(_delta_time);
		}
	}





	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T, typename ...Args>
	auto systems_manager<UserBasicSystem>::addSystem(size_t _priority, Args&&... _args) noexcept -> system_ptr_t
	{
		auto system = std::make_shared<T>(std::forward<Args>(_args)...);

		auto it = m_systems.emplace(_priority, std::make_pair(T::system_name, system));

		if (it == m_systems.end())
			return nullptr;
		
		return system;
	}



	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T> 
	auto systems_manager<UserBasicSystem>::findSystem() noexcept -> typename systems_storage_t::iterator
	{
		for (auto begin = m_systems.begin(); begin != m_systems.end(); begin++)
		{
			if (begin->second.first == T::system_name)
				return begin;
		}
		return m_systems.end();
	}



	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T>
	auto systems_manager<UserBasicSystem>::removeSystem() noexcept -> bool
	{
		auto system = findSystem<T>();
		if (system != m_systems.end())
		{
			auto it = m_systems.erase(system);
			return it != m_systems.end();
		}
		return false;
	}



	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T>
	auto systems_manager<UserBasicSystem>::enableSystem() noexcept -> void
	{
		auto system = findSystem<T>();
		if (system != m_systems.end())
			system->second.second->enable();
	}



	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T>
	auto systems_manager<UserBasicSystem>::disableSystem() noexcept -> void
	{
		auto system = findSystem<T>();
		if (system != m_systems.end())
			system->second.second->disable();
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::update(float _delta_time) -> void
	{
		for (const auto& system : m_systems)
		{
			if (!system.second.second->isActive())
				continue;

			system.second.second->preUpdate(_delta_time);
			system.second.second->update(_delta_time);
			system.second.second->postUpdate(_delta_time);
		}
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::getSystems() const noexcept -> const systems_storage_t&
	{
		return m_systems;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::removeAllSystems() noexcept -> void
	{
		m_systems.clear();
	}



	template <System UserBasicSystem>
	systems_manager<UserBasicSystem>::~systems_manager()
	{
		removeAllSystems();
	}
}