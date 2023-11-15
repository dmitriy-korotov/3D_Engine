#include <engine/ecs/components/physic/position.hpp>

#include <engine/Engine.hpp>

#include <glm/ext/matrix_transform.hpp>



namespace engine::ecs::components
{
	position::position(const glm::vec3& _position) noexcept
			: m_position(_position)
	{ }



	void position::setPosition(const glm::vec3& _position) noexcept
	{
		if (m_position != _position)
		{
			m_position = _position;
			m_is_need_update_translate_matrix = true;
		}
	}



	const glm::vec3& position::getPosition() const noexcept
	{
		return m_position;
	}



	const glm::mat4& position::getTranslateMatrix() const noexcept
	{
		if (m_is_need_update_translate_matrix)
			updateTranslateMatrix();
		return m_translate_matrix;
	}



	void position::updateTranslateMatrix() const noexcept
	{
		m_translate_matrix = glm::translate(glm::mat4(1.f), m_position);

		m_is_need_update_translate_matrix = false;
	}



	bool position::putOnUI() noexcept
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



	void position::deserializeFrom(const serialized_view_t& _serialized_view) noexcept
	{
		basic_component::deserializeFrom(_serialized_view);

		auto pos_coord = _serialized_view.at("pos").begin();

		m_position.x = *(pos_coord);		pos_coord++;
		m_position.y = *(pos_coord);		pos_coord++;
		m_position.z = *(pos_coord);
	}
}