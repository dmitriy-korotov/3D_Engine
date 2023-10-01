#include <engine/ecs/components/light_component.hpp>



namespace engine::ecs::components
{
	light_component::light_component(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept
			: m_ambient(_ambient)
			, m_diffuse(_diffuse)
			, m_specular(_specular)
	{ }



	void light_component::setFactors(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept
	{
		m_ambient = _ambient;
		m_specular = _specular;
		m_diffuse = _diffuse;
	}



	const glm::vec3& light_component::getAmbient() const noexcept
	{
		return m_ambient;
	}



	const glm::vec3& light_component::getDiffuse() const noexcept
	{
		return m_diffuse;
	}



	const glm::vec3& light_component::getSpecular() const noexcept
	{
		return m_specular;
	}
}