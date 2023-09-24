#include <engine/application.hpp>

#include <iostream>



int main(int _argc, char** _argv)
{
	engine::application::instance().setConfig("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\config\\config.json");
	
	if (engine::application::instance().start().has_value())
	{
		std::cerr << "ERROR: Can't start application";
	}
	
	return 0;
}