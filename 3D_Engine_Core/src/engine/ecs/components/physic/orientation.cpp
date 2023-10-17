#include <engine/ecs/components/physic/orientation.hpp>

#include <engine/Engine.hpp>

#include <glm/geometric.hpp>

#include <cassert>



namespace engine::ecs::components
{
	orientation::orientation(const glm::vec3& _forward, const glm::vec3& _right) noexcept
			: m_forward(glm::normalize(_forward))
			, m_right(glm::normalize(_right))
			, m_up(glm::normalize(glm::cross(m_forward, m_right)))
	{ 
		assert(glm::dot(m_forward, m_right) == 0.f);
	}



	void orientation::setOrientation(const glm::vec3& _forward, const glm::vec3& _right) noexcept
	{
		assert(glm::dot(_forward, _right) == 0.f);

		m_forward = glm::normalize(_forward);
		m_right = glm::normalize(_right);

		m_up = glm::normalize(glm::cross(m_right, m_forward));
	}



	const glm::vec3& orientation::getForward() const noexcept
	{
		return m_forward;
	}
	const glm::vec3& orientation::getRight() const noexcept
	{
		return m_forward;
	}
	const glm::vec3& orientation::getUp() const noexcept
	{
		return m_forward;
	}



	bool orientation::putOnUI() noexcept
	{
		auto& UI_module = Engine::getApplicationUIModule();

		bool is_clicked = false;

		is_clicked |= UI_module->putSliderFloat3("Fowrdard", m_forward, -1.f, 1.f);
		is_clicked |= UI_module->putSliderFloat3("Right", m_right, -1.f, 1.f);
		is_clicked |= UI_module->putSliderFloat3("Up", m_up, -1.f, 1.f);

		return is_clicked;
	}
}