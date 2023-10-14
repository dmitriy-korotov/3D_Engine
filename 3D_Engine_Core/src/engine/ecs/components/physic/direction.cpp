#include <engine/ecs/components/physic/direction.hpp>

#include <engine/Engine.hpp>



namespace engine::ecs::components
{
	direction::direction(const glm::vec3& _forward, const glm::vec3& _right, const glm::vec3& _up) noexcept
			: m_forward(_forward)
			, m_right(_right)
			, m_up(_up)
	{ }



	void direction::setForward(const glm::vec3& _forward) noexcept
	{
		m_forward = _forward;
	}
	void direction::setRight(const glm::vec3& _right) noexcept
	{
		m_right = _right;
	}
	void direction::setUp(const glm::vec3& _up) noexcept
	{
		m_up = _up;
	}



	const glm::vec3& direction::getForward() const noexcept
	{
		return m_forward;
	}
	const glm::vec3& direction::getRight() const noexcept
	{
		return m_forward;
	}
	const glm::vec3& direction::getUp() const noexcept
	{
		return m_forward;
	}



	bool direction::putOnUI() noexcept
	{
		auto& UI_module = Engine::getApplicationUIModule();

		bool is_clicked = false;

		is_clicked |= UI_module->putSliderFloat3("Fowrdard", m_forward, -1.f, 1.f);
		is_clicked |= UI_module->putSliderFloat3("Right", m_right, -1.f, 1.f);
		is_clicked |= UI_module->putSliderFloat3("Up", m_up, -1.f, 1.f);

		return is_clicked;
	}
}