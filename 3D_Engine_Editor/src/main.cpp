#include <editor_app.hpp>

#include <iostream>



int main(int argc, char** argv)
{
	try
	{
		editor_app app_(1024, 720, "3D Engine");

		if (app_.start().has_value())
		{
			std::cerr << "ERROR: Application is not started." << std::endl;
			return -1;
		}
	}
	catch (const std::exception& ex_)
	{
		std::cerr << "ERROR: Application is not started." << std::endl;
	}

	return 0;
}