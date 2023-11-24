#include <engine/scene/components/render/light/light_attenuation.hpp>

#include <engine/Engine.hpp>



namespace engine::scene::components
{
	light_attenuation::light_attenuation(float _constant, float _linear, float _quadratic) noexcept
			: m_constant(_constant)
			, m_linear(_linear)
			, m_qudratic(_quadratic)
	{ }

	
	
	auto light_attenuation::setConstant(float _constant) noexcept -> void
	{
		m_constant = _constant;
	}



	auto light_attenuation::setLinear(float _linear) noexcept -> void
	{
		m_linear = _linear;
	}



	auto light_attenuation::setQuadratic(float _quadratic) noexcept -> void
	{
		m_qudratic = _quadratic;
	}



	auto light_attenuation::getConstant() const noexcept -> float
	{
		return m_constant;
	}



	auto light_attenuation::getLinear() const noexcept -> float
	{
		return m_linear;
	}



	auto light_attenuation::getQuadratic() const noexcept -> float
	{
		return m_qudratic;
	}



	auto light_attenuation::putOnUI() noexcept -> bool
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
		auto serialized_view = scene_component::serialize();

		serialized_view["component_name"] = component_name;
		serialized_view["linear"] = m_linear;
		serialized_view["qudratic"] = m_qudratic;
		serialized_view["constant"] = m_constant;

		return serialized_view;
	}



	auto light_attenuation::deserializeFrom(const serialized_view_t& _serialized_view) noexcept -> void
	{
		scene_component::deserializeFrom(_serialized_view);

		_serialized_view.at("linear").get_to(m_linear);
		_serialized_view.at("qudratic").get_to(m_qudratic);
		_serialized_view.at("constant").get_to(m_constant);
	}
}