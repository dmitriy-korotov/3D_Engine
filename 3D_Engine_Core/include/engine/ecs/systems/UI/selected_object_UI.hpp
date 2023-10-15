#pragma once

#include <engine/ecs/systems/basic_system.hpp>

#include <engine/modules/ui/fwd/basic_UIModule.hpp>

#include <memory>



namespace engine::ecs::systems
{
	class selected_object_UI: public basic_system
	{
	public:

		using UIModule_ptr = std::shared_ptr<modules::ui::basic_UIModule>;

		selected_object_UI() noexcept;

		void preUpdate(float _delta_time) const noexcept override;
		void update(float _delta_time) const noexcept override;
		void postUpdate(float _delta_time) const noexcept override;

	private:

		const UIModule_ptr& m_UI_module;

	};
}