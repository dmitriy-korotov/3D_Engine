#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>



namespace engine::ecs::components
{
	class scale: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "scale";



		scale(const glm::vec3& _scale = glm::vec3(1.f)) noexcept;

		void setScale(const glm::vec3& _rotation) noexcept;
		const glm::vec3& getScale() const noexcept;

		const glm::mat4& getScaleMatrix() const noexcept;

		bool putOnUI() noexcept override;

	private:

		void updateScaleMatrix() const noexcept;

	private:

		glm::vec3 m_scale;

		mutable glm::mat4 m_scale_matrix = glm::mat4(1.f);
		mutable bool m_is_need_update_scale_matrix = true;

	};
}