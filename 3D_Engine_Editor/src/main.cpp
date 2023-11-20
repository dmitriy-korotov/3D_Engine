#include <editor_app.hpp>

#include <iostream>





int main(int _argc, char** _argv)
{
	auto& application = editor::Editor::instance();

	application.setConfig("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\config\\config.json");
	
	if (application.start().has_value())
	{
		std::cerr << "ERROR: Can't start application" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}