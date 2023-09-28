#include <editor_app.hpp>

#include <iostream>



int main(int _argc, char** _argv)
{
	editor::editor_app::instance().setConfig("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\config\\config.json");
	
	if (editor::editor_app::instance().start().has_value())
	{
		std::cerr << "ERROR: Can't start application";
	}

	return 0;
}