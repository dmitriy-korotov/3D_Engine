#include <engine/scene/components/components_creator.hpp>

#include <engine/logging/log.hpp>



namespace engine::scene::components
{
	components_creator::creators_map_t components_creator::m_creators;



	auto components_creator::addComponentCreator(std::string _creator_name, creatorfn_t _creator) noexcept -> bool
	{
		auto it = m_creators.emplace(std::move(_creator_name), std::make_shared<creatorfn_t>(std::move(_creator)));
		return it.second;
	}



	auto components_creator::getComponentCreator(const std::string& _creator_name) noexcept -> creatorfn_ptr_t
	{
		auto creator = m_creators.find(_creator_name);
		if (creator == m_creators.end())
		{
			LOG_ERROR("[Components creator ERROR] Creator with name '{0}' not found", _creator_name);
			return nullptr;
		}
		return creator->second;
	}
}