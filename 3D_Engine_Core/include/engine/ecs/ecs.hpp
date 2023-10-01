#pragma once

#include <string>



namespace engine::ecs
{
	namespace entities
	{
		using entity_type_id = size_t;
		using entity_id = size_t;

		constexpr entity_type_id INVALID_ENTITY_TYPE_ID = 0;
		constexpr entity_id INVALID_ENTITY_ID = 0;
	}



	namespace components
	{
		using component_type_id = size_t;
		using component_id = size_t;

		constexpr component_type_id INVALID_COMPONENT_TYPE_ID = 0;
		constexpr component_id INVALID_COMPONENT_ID = 0;
		constexpr std::string_view INVALID_COMPONENT_NAME = "";
	}



	namespace systems
	{
		using system_type_id = size_t;

		constexpr system_type_id INVALID_SYSTEM_TYPE_ID = 0;
	}
}