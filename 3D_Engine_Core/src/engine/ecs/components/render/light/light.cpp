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



	auto light::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["ambient"] = { m_ambient.x, m_ambient.y, m_ambient.z };
		serialized_view["diffuse"] = { m_diffuse.x, m_diffuse.y, m_diffuse.z };
		serialized_view["specular"] = { m_specular.x, m_specular.y, m_specular.z };

		return serialized_view;
	}



	void light::deserializeFrom(const serialized_view_t& _serialized_view) noexcept
	{
		basic_component::deserializeFrom(_serialized_view);

		auto ambient_component = _serialized_view.at("ambient").begin();

		m_ambient.x = *(ambient_component);		ambient_component++;
		m_ambient.y = *(ambient_component);		ambient_component++;
		m_ambient.z = *(ambient_component);

		auto diffuse_component = _serialized_view.at("diffuse").begin();

		m_diffuse.x = *(diffuse_component);		diffuse_component++;
		m_diffuse.y = *(diffuse_component);		diffuse_component++;
		m_diffuse.z = *(diffuse_component);

		auto specular_component = _serialized_view.at("specular").begin();

		m_specular.x = *(specular_component);		specular_component++;
		m_specular.y = *(specular_component);		specular_component++;
		m_specular.z = *(specular_component);
	}
}