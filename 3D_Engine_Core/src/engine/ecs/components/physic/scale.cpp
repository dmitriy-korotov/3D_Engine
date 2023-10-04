#include <engine/ecs/components/physic/scale.hpp>



namespace engine::ecs::components
{
	scale::scale(const glm::vec3& _scale) noexcept
			: m_scale(_scale)
	{ }



	void scale::setScale(const glm::vec3& _scale) noexcept
	{
		m_scale = _scale;
	}



	const glm::vec3& scale::getScale() const noexcept
	{
		return m_scale;
	}
}