#pragma once

#include <cstdint>



namespace engine::modules::ui
{
	enum class UIModuleImpl : uint8_t
	{
		ImGui,
		Qt,
		Juce,
		GTK_Plus
	};
}