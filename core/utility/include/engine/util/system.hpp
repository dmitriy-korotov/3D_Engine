#pragma once

#include <string>
#include <stdexcept>



namespace engine::util
{
	std::string GetEnvVariable(std::string_view _variable_name) throw(std::runtime_error);
}