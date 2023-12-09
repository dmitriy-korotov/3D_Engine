#pragma once

#include <engine/scene/Scene.hpp>



namespace engine::scene::components
{
	class light_attenuation: public virtual scene_component
	{
	public:

		static constexpr std::string_view component_name = "light_attenuation";

		light_attenuation(float _constant = 1.f, float _linear = 0.7f, float _quadratic = 1.8f) noexcept;

		void setConstant(float _constant) noexcept;
		void setLinear(float _linear) noexcept;
		void setQuadratic(float _quadratic) noexcept;

		float getConstant() const noexcept;
		float getLinear() const noexcept;
		float getQuadratic() const noexcept;

		bool putOnUI() noexcept override;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	private:

		float m_constant;
		float m_linear;
		float m_qudratic;

	};
}