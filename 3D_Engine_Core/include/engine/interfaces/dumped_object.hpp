#pragma once

#include <nlohmann/json.hpp>

#include <string>



using namespace nlohmann;

namespace engine::interfaces
{
	class serializable_object
	{
	public:

		virtual ~serializable_object() = default;

		virtual json dump() const = 0;

		virtual void load(const json& _serialized_view) = 0;

	};
}