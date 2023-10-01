#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/ext/vector_float3.hpp>
#include <glm/mat4x4.hpp>



namespace engine::ecs::components
{
	class transform_component: public basic_component
	{
	public:

		static constexpr std::string_view component_name = "transform_component";



		transform_component(glm::vec3 _position = glm::vec3(0.f),
							glm::vec3 _rotation = glm::vec3(0.f),
							glm::vec3 _scale = glm::vec3(1.f)) noexcept;

		void setTransform(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) noexcept;
		void setPosition(glm::vec3 _position) noexcept;
		void setRotation(glm::vec3 _rotation) noexcept;
		void setScale(glm::vec3 _scale) noexcept;

		const glm::mat4& getModelMatrix() noexcept;

		const glm::vec3 getPosition() const noexcept;
		const glm::vec3 getRotation() const noexcept;
		const glm::vec3 getScale() const noexcept;

	private:

		void updateModelMatrix() noexcept;

	private:

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;

		glm::mat4 m_model_matrix = glm::mat4(1.f);
		bool m_is_need_update_model_matrix;

	};
}