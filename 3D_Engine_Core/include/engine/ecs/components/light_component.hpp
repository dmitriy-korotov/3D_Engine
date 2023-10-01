#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>



namespace engine::ecs::components
{
	class light_component: public basic_component
	{
	public:

		light_component(const glm::vec3& _ambient = glm::vec3(1.f),
						const glm::vec3& _diffuse = glm::vec3(1.f),
						const glm::vec3& _specular = glm::vec3(1.f)) noexcept;

		void setFactors(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept;

		const glm::vec3& getAmbient() const noexcept;
		const glm::vec3& getDiffuse() const noexcept;
		const glm::vec3& getSpecular() const noexcept;

	private:

		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;

	};
}