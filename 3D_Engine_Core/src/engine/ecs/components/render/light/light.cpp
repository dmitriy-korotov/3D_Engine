#include <engine/ecs/components/render/light/light.hpp>



namespace engine::ecs::components
{
	light::light(const glm::vec4& _color, const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept
			: color(_color)
			, m_ambient(_ambient)
			, m_diffuse(_diffuse)
			, m_specular(_specular)
	{ }



	void light::setFactors(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept
	{
		m_ambient = _ambient;
		m_specular = _specular;
		m_diffuse = _diffuse;
	}



	const glm::vec3& light::getAmbient() const noexcept
	{
		return m_ambient;
	}



	const glm::vec3& light::getDiffuse() const noexcept
	{
		return m_diffuse;
	}



	const glm::vec3& light::getSpecular() const noexcept
	{
		return m_specular;
	}
}