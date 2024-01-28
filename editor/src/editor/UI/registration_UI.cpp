#include <editor/UI/registration_UI.hpp>

#include <engine/application_settings.hpp>

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>



namespace editor::ui
{
	auto registration_UI::update([[maybe_unused]] float _delta_time) noexcept -> void
	{
		if (!m_is_registration)
			return;

		auto winodw_size = ImVec2(engine::application_settings::instance().getWidth(),
								  engine::application_settings::instance().getHeight());

		ImGui::SetNextWindowBgAlpha(1.f);
		ImGui::SetNextWindowSize(winodw_size);

		ImGui::Begin("Registration", std::addressof(m_is_registration), ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

		ImGui::InputText("Input login", std::addressof(m_login));
		ImGui::InputText("Input password", std::addressof(m_password), ImGuiInputTextFlags_Password);
		ImGui::InputText("Repeat password", std::addressof(m_confirmed_password), ImGuiInputTextFlags_Password);
		ImGui::Checkbox("Rememder me", std::addressof(m_is_remembered));
		if (ImGui::Button("Registrate"))
			m_is_registration = false;

		ImGui::End();
	}
}