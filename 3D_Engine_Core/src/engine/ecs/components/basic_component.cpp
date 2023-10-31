#include <engine/ecs/components/basic_component.hpp>

#include <engine/logging/log.hpp>

#include <sstream>



namespace engine::ecs::components
{
	size_t basic_component::m_next_component_id = INVALID_COMPONENT_ID;





	basic_component::basic_component() noexcept
		: m_id(generateComponentID())
	{ }



	void basic_component::onConstruct() noexcept
	{ }



	bool basic_component::isActive() const noexcept
	{
		return m_is_active;
	}



	void basic_component::enable() noexcept
	{
		m_is_active = true;
	}



	void basic_component::disable() noexcept
	{
		m_is_active = false;
	}



	entities::entity_id_t basic_component::getOwner() const noexcept
	{
		return m_owner;
	}



	component_id_t basic_component::getID() const noexcept
	{
		return m_id;
	}



	void basic_component::setOwner(entities::entity_id_t _entity_id) noexcept
	{
		m_owner = _entity_id;
	}



	component_id_t basic_component::generateComponentID() noexcept
	{
		return ++m_next_component_id;
	}



	bool basic_component::putOnUI() noexcept
	{
		LOG_WARN("[Basic component WARN] Method 'putOnUI' is not overrided");
		return false;
	}



	std::string basic_component::dump() const noexcept
	{
		json serialize_view;
		std::string result;
		
		try
		{
			serialize_view["id"] = m_id;
			serialize_view["is_active"] = m_is_active;
			serialize_view["owner"] = m_owner;

			dump(serialize_view);

			result = serialize_view.dump();
		}
		catch (const std::exception& _ex)
		{
			LOG_ERROR("[Basic component ERROR] Serialize error: {0}", _ex.what());
		}

		return result;
	}



	void basic_component::load(std::string_view _dumped_view) noexcept
	{
		try
		{
			json serialize_view = json::parse(_dumped_view);
			m_id = serialize_view["id"];
			m_is_active = serialize_view["is_active"];
			m_owner = serialize_view["owner"];
		}
		catch (const std::exception& _ex)
		{
			LOG_ERROR("[Basic component ERROR] Deserialize error: {0}", _ex.what());
		}
	}



	void basic_component::dump(json& _dumped_view) const
	{ }



	void basic_component::load(const json& _dumped_view)
	{ }
}