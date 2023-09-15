#pragma once



namespace engine::ecs
{
	namespace entities
	{
		using entity_id = size_t;

		constexpr entity_id INVALID_ENTITY_ID = 0;
	}



	namespace components
	{
		using component_type_id = size_t;
		using component_id = size_t;

		constexpr component_id INVALID_COMPONENT_ID = 0;
	}
}