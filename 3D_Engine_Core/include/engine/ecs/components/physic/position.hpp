#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>



namespace engine::ecs::components
{
	class position: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "position";



		position(const glm::vec3& _position = glm::vec3(0.f)) noexcept;

		void setPosition(const glm::vec3& _position) noexcept;
		const glm::vec3& getPosition() const noexcept;

		const glm::mat4& getTranslateMatrix() const noexcept;

		bool putOnUI() noexcept override;

	private:

		void updateTranslateMatrix() const noexcept;

	private:

		glm::vec3 m_position;

		mutable glm::mat4 m_translate_matrix = glm::mat4(1.f);
		mutable bool m_is_need_update_translate_matrix = true;

	};
}