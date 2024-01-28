#pragma once

#include <engine/scene/Scene.hpp>



namespace editor::ui
{
	class registration_UI : public engine::scene::systems::scene_system
	{
	public:

		static constexpr std::string_view system_name = "registration_UI";

		void update(float _delta_time) noexcept override;

	private:

		bool m_is_registration = true;
		std::string m_login;
		std::string m_password;
		std::string m_confirmed_password;
		bool m_is_remembered = false;

	};
}