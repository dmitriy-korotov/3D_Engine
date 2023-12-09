#pragma once

#include <engine/modules/ui/basic_UIModule.hpp>



namespace engine::modules::ui::imgui
{
	class UIModule: public basic_UIModule
	{
	public:

		static UIModule& instance() noexcept;



		void initialize(const window_ptr& _window_ptr) noexcept override;
		void terminate() noexcept override;

		void onUIDrawBegin() const noexcept override;
		void onUIDrawEnd() const noexcept override;

		bool isMouseOnUI() const noexcept override;



		void begin(const std::string_view& _title) const noexcept override;
		void end() const noexcept override;

		isClicked putColorEdit4(const std::string_view& _title, glm::vec4& _color) const noexcept override;

		isClicked putSliderFloat(const std::string_view& _title, float& _value, float _min_val, float _max_val) const noexcept override;
		isClicked putSliderFloat2(const std::string_view& _title, glm::vec2& _value, float _min_val, float _max_val) const noexcept override;
		isClicked putSliderFloat3(const std::string_view& _title, glm::vec3& _value, float _min_val, float _max_val) const noexcept override;
		isClicked putSliderFloat4(const std::string_view& _title, glm::vec4& _value, float _min_val, float _max_val) const noexcept override;

		isClicked putCheckbox(const std::string_view& _title, bool& _value) const noexcept override;
		isClicked putRadioButton(const std::string_view& _title, int& _current_version, int _version) const noexcept override;

		void separate() const noexcept override;
		void newLine() const noexcept override;
		void sameLine() const noexcept override;

		void createDockSpace() const noexcept override;

	private:

		UIModule() = default;
		
		void setupImGuiConfig() const noexcept;

	};
}