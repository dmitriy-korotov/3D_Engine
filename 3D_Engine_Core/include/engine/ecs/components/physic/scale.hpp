#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>



namespace engine::ecs::components
{
	class scale: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "scale";

		scale(const glm::vec3& _scale = glm::vec3(1.f)) noexcept;

		void setScale(const glm::vec3& _rotation) noexcept;
		const glm::vec3& getScale() const noexcept;

		bool putOnUI() noexcept override;

	protected:

		glm::vec3 m_scale;

	};
}