#include <iostream>
#include <engine/application.hpp>



int main()
{
	engine::Application app_ = engine::Application::create();

	app_.start(1024, 720, "3D Engine");

	return 0;
}