#pragma once

#include <engine/util/nocopyeble.hpp>

#include <filesystem>



namespace engine
{
	class image : util::nocopyeble
	{
	public:

		image(const std::filesystem::path& _path_to_image);
		~image();

		int getWidth() const noexcept;
		int getHeight() const noexcept;
		int getChannels() const noexcept;
		const uint8_t* getData() const noexcept;
		uint8_t* getData() noexcept;

		bool isLoaded() const noexcept;

	private:

		bool m_is_loaded = false;

		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;

		uint8_t* m_data = nullptr;

	};
}