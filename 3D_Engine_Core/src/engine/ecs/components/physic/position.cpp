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
		m_position = _position;
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
		return Engine::getApplicationUIModule()->putSliderFloat3("Position", m_position, -10.f, 10.f);
	}
}