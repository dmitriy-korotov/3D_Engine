#include <editor_app.hpp>

#include <iostream>



int main(int argc, char** argv)
{
	try
	{
		editor::editor_app app_(1024, 720, "Editor");

		app_.start();
	}
	catch (const std::exception& ex_)
	{
		std::cerr << "ERROR: Application is not started." << std::endl;
	}
	
	return 0;
}