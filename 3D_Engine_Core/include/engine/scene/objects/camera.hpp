#pragma once

#include <engine/scene/scene_object.hpp>

#include <engine/render/frustum.hpp>

#include <glm/vec3.hpp>



namespace engine::scene
{
	using render::Projection;

	class camera: public scene_object
	{
	public:

		camera(const glm::vec3& _position = glm::vec3(0.f),
			   Projection _projection_mode = Projection::Perspective) noexcept;

	};
}