#pragma once

#include <engine/application.hpp>



namespace editor
{
	class Editor final: public engine::application
	{
	public:

		static Editor& instance() noexcept;

	private:

		Editor() noexcept = default;

	private:

		void onStart() noexcept override;
		void onUpdate() noexcept override;
		void onDrawUI() noexcept override;
		void onClose() noexcept override;

		void onKeyboardInput() noexcept override;
		
	};
}