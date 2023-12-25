#pragma once

#include <ctime>
#include <string>



namespace engine::util
{
	time_t GetTimeNow() noexcept;

	std::string toString(const time_t& _time) noexcept;
}