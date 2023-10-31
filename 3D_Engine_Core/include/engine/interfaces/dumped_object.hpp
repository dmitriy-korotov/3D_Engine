#pragma once

#include <nlohmann/json.hpp>

#include <string>



using namespace nlohmann;

namespace engine::interfaces
{
	class dumped_object
	{
	public:

		virtual ~dumped_object() = default;

		virtual void dump(json& _dumping_view) const = 0;

		virtual void load(const json& _dumped_view) = 0;

	};
}