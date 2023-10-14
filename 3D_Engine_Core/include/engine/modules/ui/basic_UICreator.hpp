#pragma once

#include <engine/util/nocopyeble.hpp>

#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>



namespace engine::modules::ui
{
	struct isClicked
	{
		isClicked() = default;
		isClicked(bool _is_clicked);

		operator bool() const noexcept;

	private:

		bool m_is_clicked = false;

	};

	class basic_UICreator: private util::nocopyeble
	{
	public:

		basic_UICreator() = default;
		virtual ~basic_UICreator() = default;

		virtual void begin(const std::string_view& _title) const noexcept = 0;
		virtual void end() const noexcept = 0;

		virtual isClicked putColorEdit4(const std::string_view& _title, glm::vec4& _color) const noexcept;
		
		virtual isClicked putSliderFloat(const std::string_view& _title, float& _value, float _min_val, float _max_val) const noexcept;
		virtual isClicked putSliderFloat2(const std::string_view& _title, glm::vec2& _value, float _min_val, float _max_val) const noexcept;
		virtual isClicked putSliderFloat3(const std::string_view& _title, glm::vec3& _value, float _min_val, float _max_val) const noexcept;
		virtual isClicked putSliderFloat4(const std::string_view& _title, glm::vec4& _value, float _min_val, float _max_val) const noexcept;

		virtual isClicked putCheckbox(const std::string_view& _title, bool& _value) const noexcept;
		virtual isClicked putRadioButton(const std::string_view& _title, int& _versions, int _version) const noexcept;

		virtual void separate() const noexcept;
		virtual void newLine() const noexcept;
		virtual void sameLine() const noexcept;

		virtual void createDockSpace() const noexcept;

	};
}