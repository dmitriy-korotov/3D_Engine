#include <iostream>
#include <engine/application.hpp>



int main()
{
	engine::Application app_ = engine::Application::create();

	if (app_.start(1024, 720, "3D Engine").has_value())
	{
		return -1;
	}

	return 0;
}