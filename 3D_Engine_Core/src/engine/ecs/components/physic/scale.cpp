#include <engine/ecs/components/physic/scale.hpp>

#include <engine/Engine.hpp>



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



	bool scale::putOnUI() noexcept
	{
		return Engine::getApplicationUIModule()->putSliderFloat3("Scale", m_scale, 0.1f, 10.f);
	}
}