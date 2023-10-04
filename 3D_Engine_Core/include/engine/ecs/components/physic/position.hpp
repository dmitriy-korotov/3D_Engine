#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <glm/vec3.hpp>



namespace engine::ecs::components
{
	class position: public basic_component
	{
	public:

		static constexpr std::string_view component_name = "position";

		position(const glm::vec3& _position = glm::vec3(0.f)) noexcept;

		void setPosition(const glm::vec3& _position) noexcept;
		const glm::vec3& getPosition() const noexcept;

	private:

		glm::vec3 m_position;

	};
}