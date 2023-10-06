#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <engine/render/frustum.hpp>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>



namespace engine::ecs::components
{
	using render::Projection;
	using render::orthographic_frustum;
	using render::perspective_frustum;

	class vision: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "vision";

		vision(Projection _projection_mode = Projection::Perspective) noexcept;

		void setProjectionMode(Projection _projection_mode) noexcept;
		void setOrthographicFrustum(float _right_plane, float _top_plane, float _near_plane, float _far_plane, float scale) noexcept;
		void setPrespectiveFrustum(float _fov, float _near_plane, float _far_plane) noexcept;
		void setViewPortSize(float _width, float _height) noexcept;

		const glm::mat4& getProjectionMatrix() noexcept;

	private:

		void updateProjectionMatrix() noexcept;

	private:

		Projection m_projection_mode = Projection::Perspective;

		orthographic_frustum m_orthographic_frustum;
		perspective_frustum m_perspective_frustum;

		glm::vec2 m_view_port_size = glm::vec2(0.f);

		glm::mat4 m_projection_matrix = glm::mat4(1.f);
		bool m_is_need_update_projection_matrix = true;

	};
}