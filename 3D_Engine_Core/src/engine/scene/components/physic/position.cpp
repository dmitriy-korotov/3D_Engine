#include <engine/scene/components/physic/position.hpp>

#include <engine/Engine.hpp>

#include <glm/ext/matrix_transform.hpp>



namespace engine::scene::components
{
	position::position(const glm::vec3& _position) noexcept
			: m_position(_position)
	{ }



	auto position::setPosition(const glm::vec3& _position) noexcept -> void
	{
		if (m_position != _position)
		{
			m_position = _position;
			m_is_need_update_translate_matrix = true;
		}
	}



	auto position::getPosition() const noexcept -> const glm::vec3&
	{
		return m_position;
	}



	auto position::getTranslateMatrix() const noexcept -> const glm::mat4&
	{
		if (m_is_need_update_translate_matrix)
			updateTranslateMatrix();
		return m_translate_matrix;
	}



	auto position::updateTranslateMatrix() const noexcept -> void
	{
		m_translate_matrix = glm::translate(glm::mat4(1.f), m_position);

		m_is_need_update_translate_matrix = false;
	}



	auto position::putOnUI() noexcept -> bool
	{
		bool is_clicked = Engine::getApplicationUIModule()->putSliderFloat3("Position", m_position, -10.f, 10.f);
		if (is_clicked)
			m_is_need_update_translate_matrix = true;
		return is_clicked;
	}



	auto position::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["pos"] = serialized_view_t::array({ m_position.x, m_position.y, m_position.z });

		return serialized_view;
	}



	auto position::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		basic_component::deserializeFrom(_serialized_view);

		auto pos_coord = _serialized_view.at("pos").begin();

		m_position.x = *(pos_coord);		pos_coord++;
		m_position.y = *(pos_coord);		pos_coord++;
		m_position.z = *(pos_coord);
	}
}