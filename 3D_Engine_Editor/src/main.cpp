#include <editor_app.hpp>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <iostream>

struct vertex
{
	glm::vec3 v1 = glm::vec3(1.f);
	glm::vec3 v2 = glm::vec3(1.f);
	glm::vec2 v3 = glm::vec2(1.f);
};

int main(int _argc, char** _argv)
{
	editor::editor_app::instance_t().setConfig("C:\\Users\\User\\MyProjects\\3D_Engine\\3D_Engine_Core\\res\\config\\config.json");
	
	if (editor::editor_app::instance_t().start().has_value())
	{
		std::cerr << "ERROR: Can't start application";
	}

	return 0;
}