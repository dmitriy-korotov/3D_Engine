#pragma once

#include <string>



namespace engine::interfaces
{
	class dumped_object
	{
		virtual ~dumped_object() = default;

		virtual void dump(std::string& _dumping_pool) const = 0;

		virtual void load(std::string_view _dumped_view) = 0;

	};
}