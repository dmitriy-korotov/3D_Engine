#pragma once

#include <engine/scene/Scene.hpp>

#include <glm/vec3.hpp>



namespace engine::scene::components
{
	class light: public virtual scene_component
	{
	public:

		static constexpr std::string_view component_name = "light";



		light(const glm::vec3& _ambient = glm::vec3(0.1f),
			  const glm::vec3& _diffuse = glm::vec3(1.f),
			  const glm::vec3& _specular = glm::vec3(0.5f)) noexcept;

		void setFactors(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept;

		const glm::vec3& getAmbient() const noexcept;
		const glm::vec3& getDiffuse() const noexcept;
		const glm::vec3& getSpecular() const noexcept;

		bool putOnUI() noexcept override;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	private:

		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;

	};
}