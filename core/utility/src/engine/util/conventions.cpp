#include <engine/util/conventions.hpp>

#include <sstream>



namespace engine::util
{
	std::string toString(std::thread::id _id) noexcept
	{
		std::ostringstream out;
		out << _id;
		return out.str();
	}
}