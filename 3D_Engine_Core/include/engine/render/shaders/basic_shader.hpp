#pragma once

#include <engine/util/nocopyeble.hpp>

#include <string>



namespace engine::render
{
	class basic_shader : util::nocopyeble
	{
	public:

		virtual const std::string_view& getVertexShader() const noexcept = 0;
		virtual const std::string_view& getFragmentShader() const noexcept = 0;

	};
}