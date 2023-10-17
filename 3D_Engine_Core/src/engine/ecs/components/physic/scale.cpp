#include <engine/ecs/components/physic/scale.hpp>

#include <engine/Engine.hpp>

#include <glm/ext/matrix_transform.hpp>



namespace engine::ecs::components
{
	scale::scale(const glm::vec3& _scale) noexcept
			: m_scale(_scale)
	{ }



	void scale::setScale(const glm::vec3& _scale) noexcept
	{
		if (m_scale != _scale)
		{
			m_scale = _scale;
			m_is_need_update_scale_matrix = true;
		}
	}



	const glm::vec3& scale::getScale() const noexcept
	{
		return m_scale;
	}



	const glm::mat4& scale::getScaleMatrix() const noexcept
	{
		if (m_is_need_update_scale_matrix)
			updateScaleMatrix();
		return m_scale_matrix;
	}



	void scale::updateScaleMatrix() const noexcept
	{
		m_scale_matrix = glm::scale(glm::mat4(1.f), m_scale);

		m_is_need_update_scale_matrix = false;
	}



	bool scale::putOnUI() noexcept
	{
		return Engine::getApplicationUIModule()->putSliderFloat3("Scale", m_scale, 0.1f, 10.f);
	}
}