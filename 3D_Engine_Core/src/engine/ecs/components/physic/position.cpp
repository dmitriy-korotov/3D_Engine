#include <engine/ecs/components/physic/position.hpp>



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
}