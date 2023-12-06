#include <engine/scene/components/physic/rotation.hpp>

#include <engine/Engine.hpp>

#include <glm/ext/matrix_transform.hpp>



namespace engine::scene::components
{
	rotation::rotation(const glm::vec3& _rotation) noexcept
			: m_rotation(_rotation)
	{ }



	auto rotation::setRotation(const glm::vec3& _rotation) noexcept -> void
	{
		if (m_rotation != _rotation)
		{
			m_rotation = _rotation;
			m_is_need_update_rotation_matrix = true;
		}
	}



	auto rotation::getRotation() const noexcept -> const glm::vec3&
	{
		return m_rotation;
	}



	auto rotation::getRotationMatrix() const noexcept -> const glm::mat4&
	{
		if (m_is_need_update_rotation_matrix)
			updateRotationMatrix();
		return m_rotation_matrix;
	}



	auto rotation::updateRotationMatrix() const noexcept -> void
	{
		m_rotation_matrix = glm::rotate(glm::mat4(1.f), m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		m_rotation_matrix = glm::rotate(m_rotation_matrix, m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		m_rotation_matrix = glm::rotate(m_rotation_matrix, m_rotation.z, glm::vec3(0.f, 0.f, 1.f));

		m_is_need_update_rotation_matrix = false;
	}



	auto rotation::putOnUI() noexcept -> bool
	{
		bool is_clicked = Engine::getApplicationUIModule()->putSliderFloat3("Rotation", m_rotation, -360.f, 360.f);
		if (is_clicked)
			m_is_need_update_rotation_matrix = true;
		return is_clicked;
	}



	auto rotation::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = scene_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["rotation"] = serialized_view_t::array({ m_rotation.x, m_rotation.y, m_rotation.z });

		return serialized_view;
	}



	auto rotation::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		scene_component::deserializeFrom(_serialized_view);

		auto rotation_coord = _serialized_view.at("rotation").begin();

		m_rotation.x = *(rotation_coord);		rotation_coord++;
		m_rotation.y = *(rotation_coord);		rotation_coord++;
		m_rotation.z = *(rotation_coord);
	}
}