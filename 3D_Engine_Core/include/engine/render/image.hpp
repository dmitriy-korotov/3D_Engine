#pragma once

#include <engine/util/nocopyeble.hpp>

#include <filesystem>



namespace engine::render
{
	using std::filesystem::path;

	class image : util::nocopyeble
	{
	public:

		image(const path& _path_to_image);
		~image();

		int getWidth() const noexcept;
		int getHeight() const noexcept;
		int getChannels() const noexcept;
		const std::byte* getData() const noexcept;
		std::byte* getData() noexcept;

		bool isLoaded() const noexcept;

	private:

		bool m_is_loaded = false;

		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;
		
		std::byte* m_data = nullptr;

	};
}