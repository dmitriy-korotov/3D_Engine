#include <engine/ecs/components/render/light/light_attenuation.hpp>

#include <engine/Engine.hpp>



namespace engine::ecs::components
{
	light_attenuation::light_attenuation(float _constant, float _linear, float _quadratic) noexcept
			: m_constant(_constant)
			, m_linear(_linear)
			, m_qudratic(_quadratic)
	{ }

	
	
	void light_attenuation::setConstant(float _constant) noexcept
	{
		m_constant = _constant;
	}



	void light_attenuation::setLinear(float _linear) noexcept
	{
		m_linear = _linear;
	}



	void light_attenuation::setQuadratic(float _quadratic) noexcept
	{
		m_qudratic = _quadratic;
	}



	float light_attenuation::getConstant() const noexcept
	{
		return m_constant;
	}



	float light_attenuation::getLinear() const noexcept
	{
		return m_linear;
	}



	float light_attenuation::getQuadratic() const noexcept
	{
		return m_qudratic;
	}



	bool light_attenuation::putOnUI() noexcept
	{
		bool is_clicked = false;

		const auto& UI_module = Engine::getApplicationUIModule();

		is_clicked |= UI_module->putSliderFloat("Constant", m_constant, 0.f, 2.f);
		is_clicked |= UI_module->putSliderFloat("Linear", m_linear, 0.f, 1.f);
		is_clicked |= UI_module->putSliderFloat("Quadratic", m_qudratic, 0.f, 2.f);

		return is_clicked;
	}



	auto light_attenuation::serialize() const noexcept -> serialized_view_t
	{
		auto serialized_view = basic_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["linear"] = m_linear;
		serialized_view["qudratic"] = m_qudratic;
		serialized_view["constant"] = m_constant;

		return serialized_view;
	}



	void light_attenuation::deserializeFrom(const serialized_view_t& _serialized_view) noexcept
	{
		basic_component::deserializeFrom(_serialized_view);

		_serialized_view.at("linear").get_to(m_linear);
		_serialized_view.at("qudratic").get_to(m_qudratic);
		_serialized_view.at("constant").get_to(m_constant);
	}
}