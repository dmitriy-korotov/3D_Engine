#pragma once

#include <engine/application.hpp>



class editor_app : public engine::application
{
public:

	editor_app(uint16_t _width, uint16_t _height,
			   const std::string_view& _editor_name);

};