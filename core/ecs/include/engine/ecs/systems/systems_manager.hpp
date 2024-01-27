#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/ecs/systems/basic_system.hpp>

#include <map>
#include <memory>
#include <concepts>



namespace engine::ecs::systems
{
	template <System UserBasicSystem>
	class systems_manager : private util::nocopyeble
	{
	public:

		using system_ptr_t = std::shared_ptr<UserBasicSystem>;



		systems_manager() = default;

		void update(float _delta_time);

		bool addSystemsGroup(const std::string& _group_name, size_t _group_priority) noexcept;
		bool removeSystemsGroup(const std::string& _group_name) noexcept;
		void removeAllSystemsGroups() noexcept;

		void enableGroup(const std::string& _group_name) noexcept;
		void disableGroup(const std::string& _group_name) noexcept;

		template <std::derived_from<UserBasicSystem> T, typename ...Args>
		[[nodiscard]] system_ptr_t addSystem(const std::string& _group_name, size_t _priority, Args&&... _args) noexcept;

		std::vector<system_ptr_t> getSystems() const noexcept;

		template <std::derived_from<UserBasicSystem> T>
		bool removeSystem() noexcept;

		template <std::derived_from<UserBasicSystem> T>
		void enableSystem() noexcept;

		template <std::derived_from<UserBasicSystem> T>
		void disableSystem() noexcept;

		void removeAllSystems() noexcept;

	private:

		using systems_storage_t = std::map<size_t, system_ptr_t>;
		using name_to_location_map_t = std::unordered_map<std::string, std::pair<size_t, size_t>>;

	private:

		class systems_group
		{
		public:

			explicit systems_group(std::string _group_name) noexcept;

			const std::string& getName() const noexcept;
			const systems_storage_t& getSystemsStorage() const noexcept;

			bool addSystem(system_ptr_t _system, size_t _priority_into_group) noexcept;
			
			bool removeSystem(size_t _system_priority) noexcept;
			void removeSystems() noexcept;

			bool isActive() const noexcept;
			void enable() noexcept;
			void disable() noexcept;

			void update(float _delta_time);

		private:

			std::string m_name;
			systems_storage_t m_systems;
			bool m_is_active = true;

		};

		using groups_storage_t = std::map<size_t, systems_group>;

	private:

		typename groups_storage_t::iterator findGroup(const std::string& _group_name) noexcept;

		template <std::derived_from<UserBasicSystem> T>
		typename system_ptr_t findSystem() noexcept;

	private:

		groups_storage_t m_groups;
		name_to_location_map_t m_systems_locations;		// mapping for fast search systems

	};





	template <System UserBasicSystem>
	systems_manager<UserBasicSystem>::template systems_group::systems_group(std::string _group_name) noexcept
			: m_name(std::move(_group_name))
	{ }



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::getName() const noexcept -> const std::string&
	{
		return m_name;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::getSystemsStorage() const noexcept -> const systems_storage_t&
	{
		return m_systems;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::addSystem(system_ptr_t _system, size_t _priority_into_group) noexcept -> bool
	{
		auto result = m_systems.emplace(_priority_into_group, std::move(_system));
		return result.second;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::removeSystem(size_t _system_priority) noexcept -> bool
	{
		return m_systems.erase(_system_priority);
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::removeSystems() noexcept -> void
	{
		m_systems.clear();
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::isActive() const noexcept -> bool
	{
		return m_is_active;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::enable() noexcept -> void
	{
		m_is_active = true;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::disable() noexcept -> void
	{
		m_is_active = false;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::template systems_group::update(float _delta_time) -> void
	{
		for (auto& [priority, system] : m_systems)
		{
			if (!system->isActive())
				continue;

			system->preUpdate(_delta_time);
			system->update(_delta_time);
			system->postUpdate(_delta_time);
		}
	}





	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::addSystemsGroup(const std::string& _group_name, size_t _priority) noexcept -> bool
	{
		auto group_it = findGroup(_group_name);
		if (group_it != m_groups.end())
		{
			LOG_WARN("[Systems manager WARN] System with name '{0}' already exists", _group_name);
			return false;
		}
		return m_groups.emplace(_priority, systems_group(_group_name)).second;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::removeSystemsGroup(const std::string& _group_name) noexcept -> bool
	{
		auto group_it = findGroup(_group_name);
		if (group_it == m_groups.end())
			return false;

		for (auto [system_priority, system] : group_it->second.getSystemsStorage())
			m_systems_locations.erase(std::string(system->system_name));

		return (m_groups.erase(group_it) != m_groups.end());
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::removeAllSystemsGroups() noexcept -> void
	{
		m_groups.clear();
		m_systems_locations.clear();
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::enableGroup(const std::string& _group_name) noexcept -> void
	{
		auto group_it = findGroup(_group_name);
		if (group_it != m_groups.end())
			group_it->second.enable();
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::disableGroup(const std::string& _group_name) noexcept -> void
	{
		auto group_it = findGroup(_group_name);
		if (group_it != m_groups.end())
			group_it->second.disable();
	}



	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T, typename ...Args>
	auto systems_manager<UserBasicSystem>::addSystem(const std::string& _group_name, size_t _priority, Args&&... _args) noexcept -> system_ptr_t
	{
		auto system = std::make_shared<T>(std::forward<Args>(_args)...);

		auto group_it = findGroup(_group_name);
		if (group_it == m_groups.end())
		{
			LOG_ERROR("[Systems manager ERROR] Group '{0}' is not exists", _group_name);
			return nullptr;
		}

		bool success = group_it->second.addSystem(system, _priority);
		if (!success)
			return nullptr;

		if (!m_systems_locations.emplace(std::string(T::system_name), std::make_pair(group_it->first, _priority)).second)
		{
			LOG_CRITICAL("[Systems manager CRITICAL] Group '{0}', system '{1}' incorrect add operation finish", _group_name, std::string(T::system_name));
			return nullptr;
		}

		return system;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::findGroup(const std::string& _group_name) noexcept -> typename groups_storage_t::iterator
	{
		for (auto begin = m_groups.begin(); begin != m_groups.end(); begin++)
		{
			if (begin->second.getName() == _group_name)
				return begin;
		}
		return m_groups.end();
	}



	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T> 
	auto systems_manager<UserBasicSystem>::findSystem() noexcept -> typename system_ptr_t
	{
		auto system_name = std::string(T::system_name);
		if (!m_systems_locations.contains(system_name))
			return nullptr;

		auto [group_priority, system_priority] = m_systems_locations[system_name];
		const auto& group_systems = m_groups[group_priority].getSystemsStorage();
		return group_systems[system_priority];
	}



	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T>
	auto systems_manager<UserBasicSystem>::removeSystem() noexcept -> bool
	{
		auto system_name = std::string(T::system_name);
		if (!m_systems_locations.contains(system_name))
			return false;

		auto [group_priority, system_priority] = m_systems_locations[system_name];
		m_systems_locations.erase(system_name);
		return m_groups[group_priority].removeSystem(system_priority);
	}



	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T>
	auto systems_manager<UserBasicSystem>::enableSystem() noexcept -> void
	{
		auto system = findSystem<T>();
		if (system != nullptr)
			system->enable();
	}



	template <System UserBasicSystem>
	template <std::derived_from<UserBasicSystem> T>
	auto systems_manager<UserBasicSystem>::disableSystem() noexcept -> void
	{
		auto system = findSystem<T>();
		if (system != nullptr)
			system->disable();
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::update(float _delta_time) -> void
	{
		for (auto& [priority, group] : m_groups)
		{
			if (!group.isActive())
				continue;

			group.update(_delta_time);
		}
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::getSystems() const noexcept -> std::vector<system_ptr_t>
	{
		std::vector<system_ptr_t> systems;
		for (const auto& [group_priority, group] : m_groups)
		{
			for (const auto& [system_proirity, system] : group.getSystemsStorage())
			{
				systems.push_back(system);
			}
		}
		return systems;
	}



	template <System UserBasicSystem>
	auto systems_manager<UserBasicSystem>::removeAllSystems() noexcept -> void
	{
		for (auto& [priority, group] : m_groups)
			group.removeSystems();
		m_systems_locations.clear();
	}
}