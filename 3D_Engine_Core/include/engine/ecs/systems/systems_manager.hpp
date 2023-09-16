#pragma once

#include <vector>
#include <memory>



namespace engine::ecs::systems
{
	class basic_system;

	class systems_manager
	{
	public:

		using system_ptr = std::shared_ptr<basic_system>;
		using systems_storage = std::vector<system_ptr>;

		void update(float _delta_time);

		template <typename SystemType, typename ...Args>
		void addSystem(Args&&... _args) noexcept;

	private:

		systems_storage m_systems;

	};



	template <typename SystemType, typename ...Args>
	void systems_manager::addSystem(Args&&... _args) noexcept
	{
		static_assert(std::is_base_of_v<basic_system, SystemType>, "SystemType is not derived basic_system.");

		m_systems.push_back(std::make_shared<SystemType>(std::forward<Args>(_args)...));
	}
}