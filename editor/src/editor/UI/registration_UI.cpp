#include <editor/UI/registration_UI.hpp>

#include <engine/application_settings.hpp>

#include <editor/controllers/registration_controller.hpp>

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>





static bool s_is_passwords_not_equal = false;





namespace editor::ui
{
	auto registration_UI::preUpdate(float _delta_time) noexcept -> void
	{
		auto winodw_size = ImVec2(engine::application_settings::instance().getWidth(),
								  engine::application_settings::instance().getHeight());

		ImGui::SetNextWindowBgAlpha(1.f);
		ImGui::SetNextWindowSize(winodw_size);

		ImGui::Begin("Registration", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	}



	auto registration_UI::update([[maybe_unused]] float _delta_time) noexcept -> void
	{
		ImGui::InputText("Input login", std::addressof(m_login));
		ImGui::InputText("Input email/phone", std::addressof(m_email));

		if (s_is_passwords_not_equal)
			ImGui::PushStyleColor(ImGuiCol_Text, { 255.f, 0.f, 0.f, 1.f });
		ImGui::InputText("Input password", std::addressof(m_password), ImGuiInputTextFlags_Password);
		if (s_is_passwords_not_equal)
			ImGui::PopStyleColor(1);

		if (s_is_passwords_not_equal)
			ImGui::PushStyleColor(ImGuiCol_Text, { 255.f, 0.f, 0.f, 1.f });
		ImGui::InputText("Repeat password", std::addressof(m_confirmed_password), ImGuiInputTextFlags_Password);
		if (s_is_passwords_not_equal)
			ImGui::PopStyleColor(1);

		ImGui::Checkbox("Rememder me", std::addressof(m_is_remembered));

		if (ImGui::Button("Registrate"))
		{
			if (m_password != m_confirmed_password)
			{
				s_is_passwords_not_equal = true;
				return;
			}

			auth::user user(std::move(m_login), auth::email_t{ .email = std::move(m_email) }, m_password);

			controllers::registration_controller::registrateUser(user);

			disable();
		}
	}



	auto registration_UI::postUpdate(float _delta_time) noexcept -> void
	{
		ImGui::End();
	}
}