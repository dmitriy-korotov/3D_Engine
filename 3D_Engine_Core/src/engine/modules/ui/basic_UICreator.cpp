#include <engine/modules/ui/basic_UICreator.hpp>

#include <engine/logging/log.hpp>



namespace engine::modules::ui
{
	isClicked::isClicked(bool _is_clicked)
			: m_is_clicked(_is_clicked)
	{ }



	isClicked::operator bool() const noexcept
	{
		return m_is_clicked;
	}



	isClicked basic_UICreator::putColorEdit4(const std::string_view& _title, glm::vec4& _color) const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'putColorEdit4' is not overloaded");
		return {};
	}
	isClicked basic_UICreator::putSliderFloat(const std::string_view& _title, float& _value, float _min_val, float _max_val) const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'putSliderFloat' is not overloaded");
		return {};
	}
	isClicked basic_UICreator::putSliderFloat2(const std::string_view& _title, glm::vec2& _value, float _min_val, float _max_val) const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'putSliderFloat2' is not overloaded");
		return {};
	}
	isClicked basic_UICreator::putSliderFloat3(const std::string_view& _title, glm::vec3& _value, float _min_val, float _max_val) const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'putSliderFloat3' is not overloaded");
		return {};
	}
	isClicked basic_UICreator::putSliderFloat4(const std::string_view& _title, glm::vec4& _value, float _min_val, float _max_val) const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'putSliderFloat4' is not overloaded");
		return {};
	}
	isClicked basic_UICreator::putCheckbox(const std::string_view& _title, bool& _value) const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'putCheckbox' is not overloaded");
		return {};
	}
	isClicked basic_UICreator::putRadioButton(const std::string_view& _title, int& _current_version, int _version) const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'putRadioButton' is not overloaded");
		return {};
	}
	void basic_UICreator::separate() const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'Separate' is not overloaded");
	}
	void basic_UICreator::newLine() const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'newLine' is not overloaded");
	}
	void basic_UICreator::sameLine() const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'sameLine' is not overloaded");
	}
	void basic_UICreator::createDockSpace() const noexcept
	{
		LOG_WARN("[Basic UI Module WARN] Method 'createDockSpace' is not overloaded");
	}
}