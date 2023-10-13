#include <editor_app.hpp>

#include <iostream>





using editor::Editor;

int main(int _argc, char** _argv)
{
	Editor::instance().setConfig("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\config\\config.json");
	
	if (Editor::instance().start().has_value())
		std::cerr << "ERROR: Can't start application" << std::endl;

	return 0;
}