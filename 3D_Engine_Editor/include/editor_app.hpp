#pragma once

#include <engine/application.hpp>



namespace editor
{
	class editor_app final: public engine::application
	{
	public:

		static editor_app& instance() noexcept;

		editor_app() noexcept = default;

	private:

		void setEventListeners() noexcept;
		void onStart() noexcept override;
		void onUpdate() noexcept override;
		void onDrawUI() noexcept override;
		void onClose() noexcept override;

	};
}