#include <engine/util/conventions.hpp>

#include <sstream>



namespace engine::util
{
	auto toString(std::thread::id _id) noexcept -> std::string
	{
		std::ostringstream out;
		out << _id;
		return out.str();
	}
}