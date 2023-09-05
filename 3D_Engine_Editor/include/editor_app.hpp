#pragma once

#include <engine/application.hpp>



namespace engine::render
{
	class camera;
}

namespace editor
{
	class editor_app final : public engine::application
	{
	public:

		editor_app(uint16_t _width, uint16_t _height,
				   const std::string_view& _editor_name);
		~editor_app() override;

		void onUpdate() noexcept override;

	private:

		void setEventListeners() const noexcept;
		void drawUI() noexcept;

	private:

		std::unique_ptr<engine::render::camera> m_camera;

	};
}