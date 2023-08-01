#include <iostream>
#include <engine/application.hpp>



int main(int argc, char** argv)
{
	engine::Application app_ = engine::Application::create(1024, 720, "3D Engine");

	if (app_.start().has_value())
	{
		return -1;
	}

	return 0;
}