#include <engine/util/system.hpp>

#include <format>



namespace engine::util
{
	auto GetEnvVariable(std::string_view _variable_name) throw(std::runtime_error) -> std::string
	{
		char* var = getenv(_variable_name.data());
		if (var == nullptr)
			throw std::runtime_error(std::format("Environment variable with name '{}' is not exists", _variable_name));
		return std::string(var);
	}

}