#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>



namespace engine::ecs::components
{
	class rotation:	public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "rotation";



		rotation(const glm::vec3& _rotation = glm::vec3(0.f)) noexcept;

		void setRotation(const glm::vec3& _rotation) noexcept;
		const glm::vec3& getRotation() const noexcept;

		const glm::mat4& getRotationMatrix() const noexcept;

		bool putOnUI() noexcept override;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	private:

		void updateRotationMatrix() const noexcept;

	private:

		glm::vec3 m_rotation;

		mutable glm::mat4 m_rotation_matrix = glm::mat4(1.f);
		mutable bool m_is_need_update_rotation_matrix = true;

	};
}