#pragma once

#include <string>



namespace engine::ecs
{
	namespace entities
	{
		using entity_id_t = size_t;
		
		constexpr entity_id_t INVALID_ENTITY_ID = 0;
	}



	namespace components
	{
		using component_id_t = size_t;

		constexpr component_id_t INVALID_COMPONENT_ID = 0;
		
		constexpr std::string_view INVALID_COMPONENT_NAME = "";
	}



	namespace systems
	{
		using system_id_t = size_t;

		constexpr system_id_t INVALID_SYSTEM_ID = 0;
	}
}