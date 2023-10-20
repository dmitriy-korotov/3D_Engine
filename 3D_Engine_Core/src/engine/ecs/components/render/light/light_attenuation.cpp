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
}