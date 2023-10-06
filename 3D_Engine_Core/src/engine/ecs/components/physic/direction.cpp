#include <engine/ecs/components/physic/direction.hpp>



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
}