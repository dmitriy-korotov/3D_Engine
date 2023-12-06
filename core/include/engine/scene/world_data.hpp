#pragma once

#include <glm/vec3.hpp>



namespace engine::scene
{
	constexpr glm::vec3 g_world_up_direction =			glm::vec3(0.f, 0.f, 1.f);
	constexpr glm::vec3 g_world_right_direction =		glm::vec3(0.f, -1.f, 0.f);
	constexpr glm::vec3 g_world_forward_direction =		glm::vec3(1.f, 0.f, 0.f);
}