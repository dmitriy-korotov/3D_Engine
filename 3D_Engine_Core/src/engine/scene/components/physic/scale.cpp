#include <engine/scene/components/physic/scale.hpp>

#include <engine/Engine.hpp>

#include <glm/ext/matrix_transform.hpp>



namespace engine::scene::components
{
	scale::scale(const glm::vec3& _scale) noexcept
			: m_scale(_scale)
	{ }



	auto scale::setScale(const glm::vec3& _scale) noexcept -> void
	{
		if (m_scale != _scale)
		{
			m_scale = _scale;
			m_is_need_update_scale_matrix = true;
		}
	}



	auto scale::getScale() const noexcept -> const glm::vec3&
	{
		return m_scale;
	}



	auto scale::getScaleMatrix() const noexcept -> const glm::mat4&
	{
		if (m_is_need_update_scale_matrix)
			updateScaleMatrix();
		return m_scale_matrix;
	}



	auto scale::updateScaleMatrix() const noexcept -> void
	{
		m_scale_matrix = glm::scale(glm::mat4(1.f), m_scale);

		m_is_need_update_scale_matrix = false;
	}



	auto scale::putOnUI() noexcept -> bool
	{
		bool is_clicked = Engine::getApplicationUIModule()->putSliderFloat3("Scale", m_scale, 0.1f, 10.f);
		if (is_clicked)
			m_is_need_update_scale_matrix = true;
		return is_clicked;
	}



	auto scale::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = scene_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["scale"] = serialized_view_t::array({ m_scale.x, m_scale.y, m_scale.z });

		return serialized_view;
	}



	auto scale::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		scene_component::deserializeFrom(_serialized_view);

		auto scale_component = _serialized_view.at("scale").begin();

		m_scale.x = *(scale_component);		scale_component++;
		m_scale.y = *(scale_component);		scale_component++;
		m_scale.z = *(scale_component);
	}
}