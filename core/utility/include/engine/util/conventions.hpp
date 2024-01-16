#pragma once

#include <thread>
#include <string>



namespace engine::util
{
	std::string toString(std::thread::id _id) noexcept;
}