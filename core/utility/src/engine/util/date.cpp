#include <engine/util/date.hpp>

#include <chrono>



namespace engine::util
{
	auto GetTimeNow() noexcept -> time_t
	{
		auto time = std::chrono::system_clock::now();
		return std::chrono::system_clock::to_time_t(time);
	}



	auto toString(const time_t& _time) noexcept -> std::string
	{
		auto string_date = std::string(std::ctime(&_time));
		string_date.pop_back();
		return string_date;
	}
}