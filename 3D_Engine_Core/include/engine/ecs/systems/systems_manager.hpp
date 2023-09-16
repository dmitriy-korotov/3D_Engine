#pragma once

#include <vector>
#include <memory>



namespace engine::ecs::systems
{
	class basic_system;

	class systems_manager
	{
	public:

		using system_ptr = std::unique_ptr<basic_system>;
		using systems_storage = std::vector<system_ptr>;

		void update(float _delta_time);

	private:

		systems_storage m_systems;

	};
}