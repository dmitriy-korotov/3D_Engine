#include <engine/ecs/components/render/light/light.hpp>

#include <engine/Engine.hpp>



namespace engine::ecs::components
{
	light::light(const glm::vec3& _ambient, const glm::vec3& _diffuse, const glm::vec3& _specular) noexcept
			: m_ambient(_ambient)
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



	bool light::putOnUI() noexcept
	{
		bool is_clicked = false;

		auto& UI_module = Engine::getApplicationUIModule();

		is_clicked |= UI_module->putSliderFloat3("Ambient", m_ambient, 0.f, 1.f);
		is_clicked |= UI_module->putSliderFloat3("Diffuse", m_diffuse, 0.f, 1.f);
		is_clicked |= UI_module->putSliderFloat3("Specular", m_specular, 0.f, 1.f);

		return is_clicked;
	}
}