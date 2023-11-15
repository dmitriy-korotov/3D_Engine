#pragma once

#include <engine/ecs/components/components_manager.hpp>

#include <unordered_map>
#include <string>
#include <functional>
#include <memory>



namespace engine::ecs::components
{
	class components_creator
	{
	public:

		using creatorfn_t = std::function<components_manager::component_ptr_t<basic_component>()>;
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

		components_creator::addComponentCreator(ComponentType::component_name,
			[]() -> components_manager::component_ptr_t<basic_component>
			{
				return components_manager::addComponent<ComponentType>();
			});
	}
}