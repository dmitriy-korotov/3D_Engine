#pragma once

#include <engine/util/nocopyeble.hpp>

#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>



namespace engine::modules::ui
{
	class basic_UICreator: private util::nocopyeble
	{
	public:

		basic_UICreator() = default;
		virtual ~basic_UICreator() = default;

		virtual void begin(const std::string_view& _title) const noexcept = 0;
		virtual void end() const noexcept = 0;

		virtual void putColorEdit4(const std::string_view& _title, glm::vec4& _color) const noexcept;
		
		virtual void putSliderFloat(const std::string_view& _title, float& _value, float _min_val, float _max_val) const noexcept;
		virtual void putSliderFloat2(const std::string_view& _title, glm::vec2& _value, float _min_val, float _max_val) const noexcept;
		virtual void putSliderFloat3(const std::string_view& _title, glm::vec3& _value, float _min_val, float _max_val) const noexcept;
		virtual void putSliderFloat4(const std::string_view& _title, glm::vec4& _value, float _min_val, float _max_val) const noexcept;

		virtual void putCheckbox() const noexcept;

		virtual void Separate() const noexcept;

		virtual void createDockSpace() const noexcept;

	};
}