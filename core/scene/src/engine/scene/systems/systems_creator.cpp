#include <engine/scene/systems/systems_creator.hpp>

#include <engine/logging/log.hpp>



namespace engine::scene::systems
{
	systems_creator::creators_map_t systems_creator::m_creators = { };



	auto systems_creator::addCreator(std::string _system_name, creatorfn_t _creator_function) noexcept -> bool
	{
		return m_creators.emplace(std::move(_system_name), std::make_shared<creatorfn_t>(std::move(_creator_function))).second;
	}



	auto systems_creator::getSystemCreator(const std::string& _system_name) noexcept -> creatorfn_ptr_t
	{
		auto creator = m_creators.find(_system_name);
		if (creator == m_creators.end())
		{
			LOG_ERROR("[Systems creator ERROR] Creator with system name '{0}' not found", _system_name);
			return nullptr;
		}
		return creator->second;
	}
}