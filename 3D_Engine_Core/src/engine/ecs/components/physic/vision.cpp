#include <engine/ecs/components/physic/vision.hpp>

#include <engine/Engine.hpp>

#include <glm/gtc/matrix_transform.hpp>



namespace engine::ecs::components
{
	vision::vision(Projection _projection_mode) noexcept
			: m_projection_mode(_projection_mode)
	{ }



	void vision::setProjectionMode(Projection _projection_mode) noexcept
	{
		if (m_projection_mode != _projection_mode)
		{
			m_projection_mode = _projection_mode;
			m_is_need_update_projection_matrix = true;
		}
	}



	void vision::setOrthographicFrustum(float _right_plane, float _top_plane, float _near_plane, float _far_plane, float _scale) noexcept
	{
		m_orthographic_frustum.right_plane = _right_plane;
		m_orthographic_frustum.top_plane = _top_plane;
		m_orthographic_frustum.near_plane = _near_plane;
		m_orthographic_frustum.far_plane = _far_plane;
		m_orthographic_frustum.scale = _scale;

		m_is_need_update_projection_matrix = true;
	}



	void vision::setPrespectiveFrustum(float _fov, float _near_plane, float _far_plane) noexcept
	{
		m_perspective_frustum.field_of_view = _fov;
		m_perspective_frustum.near_plane = _near_plane;
		m_perspective_frustum.far_plane = _far_plane;

		m_is_need_update_projection_matrix = true;
	}



	void vision::setViewPortSize(float _width, float _height) noexcept
	{
		if (m_view_port_size.x != _width || m_view_port_size.y != _height)
		{
			m_view_port_size.x = _width;
			m_view_port_size.y = _height;
			m_is_need_update_projection_matrix = true;
		}
	}



	const glm::mat4& vision::getProjectionMatrix() const noexcept
	{
		if (m_is_need_update_projection_matrix)
			updateProjectionMatrix();
		return m_projection_matrix;
	}



	void vision::updateProjectionMatrix() const noexcept
	{
		const float aspect = m_view_port_size.x / m_view_port_size.y;
		switch (m_projection_mode)
		{
		case engine::render::Projection::Orthographic:
			m_projection_matrix = glm::ortho(-m_orthographic_frustum.scale, m_orthographic_frustum.scale,
											 -m_orthographic_frustum.scale * aspect, m_orthographic_frustum.scale * aspect,
											 m_orthographic_frustum.near_plane, m_orthographic_frustum.far_plane);
			break;
		case engine::render::Projection::Perspective:
			m_projection_matrix = glm::perspective(glm::radians(m_perspective_frustum.field_of_view), aspect,
												   m_perspective_frustum.near_plane, m_perspective_frustum.far_plane);
			break;
		}
		m_is_need_update_projection_matrix = false;
	}



	bool vision::putOnUI() noexcept
	{
		auto& UI_module = Engine::getApplicationUIModule();

		bool is_clicked = false;

		static int versions = -1;
		if (UI_module->putRadioButton("Orthographic", versions, 0))
		{
			setProjectionMode(Projection::Orthographic);
			is_clicked = true;
		}
		if (UI_module->putRadioButton("Perspective", versions, 1))
		{
			setProjectionMode(Projection::Perspective);
			is_clicked = true;
		}

		return is_clicked;
	}



	auto vision::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;
		
		serialized_view["proj_mode"] = static_cast<int>(m_projection_mode);

		serialized_view["PF"]["far_plane"] = m_perspective_frustum.far_plane;
		serialized_view["PF"]["near_plane"] = m_perspective_frustum.near_plane;
		serialized_view["PF"]["fov"] = m_perspective_frustum.field_of_view;

		serialized_view["OF"]["far_plane"] = m_orthographic_frustum.far_plane;
		serialized_view["OF"]["near_plane"] = m_orthographic_frustum.near_plane;
		serialized_view["OF"]["right_plane"] = m_orthographic_frustum.right_plane;
		serialized_view["OF"]["top_plane"] = m_orthographic_frustum.top_plane;
		serialized_view["OF"]["scale"] = m_orthographic_frustum.scale;

		return serialized_view;
	}



	void vision::deserializeFrom(const serialized_view_t& _serialized_view) noexcept
	{
		basic_component::deserializeFrom(_serialized_view);

		_serialized_view.at("proj_mode").get_to(m_projection_mode);

		_serialized_view.at("PF").at("far_plane").get_to(m_perspective_frustum.far_plane);
		_serialized_view.at("PF").at("near_plane").get_to(m_perspective_frustum.near_plane);
		_serialized_view.at("PF").at("fov").get_to(m_perspective_frustum.field_of_view);

		_serialized_view.at("OF").at("far_plane").get_to(m_orthographic_frustum.far_plane);
		_serialized_view.at("OF").at("near_plane").get_to(m_orthographic_frustum.near_plane);
		_serialized_view.at("OF").at("right_plane").get_to(m_orthographic_frustum.right_plane);
		_serialized_view.at("OF").at("top_plane").get_to(m_orthographic_frustum.top_plane);
		_serialized_view.at("OF").at("scale").get_to(m_orthographic_frustum.scale);
	}
}