
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

		static editor_app& instance() noexcept;

		editor_app() noexcept;

		void init() noexcept override;
		void onUpdate() noexcept override;

	private:

		void setEventListeners() noexcept;
		void drawUI() noexcept;

	private:

		//std::unique_ptr<engine::render::camera> m_camera;

	};
}