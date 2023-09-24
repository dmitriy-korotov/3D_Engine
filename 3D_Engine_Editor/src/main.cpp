#include <engine/application.hpp>

#include <iostream>



int main(int _argc, char** _argv)
{
	engine::application::instance().start();
	
	return 0;
}