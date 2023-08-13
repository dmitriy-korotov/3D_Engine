#include <engine/application.hpp>

#include <iostream>



int main(int argc, char** argv)
{
	try
	{
		engine::Application app_ = engine::Application::create(1024, 720, "3D Engine");

		if (app_.start().has_value())
		{
			return -1;
		}
	}
	catch (const std::exception& ex_)
	{
		std::cerr << "ERROR: Application not started." << std::endl;
	}

	return 0;
}