#pragma once

#include <nlohmann/json.hpp>

#include <string>



namespace engine::interfaces
{
	class serializable_object
	{
	public:

		using serialized_view_t = nlohmann::json;

		virtual ~serializable_object() = default;

		virtual serialized_view_t serialize() const = 0;

		virtual void deserializeFrom(const serialized_view_t& _serialized_view) = 0;

	};
}