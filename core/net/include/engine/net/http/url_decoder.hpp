#pragma once

#include <engine/util/noconstructible.hpp>

#include <string>



namespace engine::net::http
{
	class url_decoder : private util::noconstructible
	{
	public:

		static std::string decode(const std::string& _url) noexcept;

	};
}