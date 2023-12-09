#pragma once

#include <engine/util/nocopyeble.hpp>

#include <filesystem>



namespace engine::util
{
	using std::filesystem::path;

	class image: private util::nocopyeble
	{
	public:

		image(const path& _path_to_image);
		image(image&& _other) noexcept;
		image& operator=(image&& _right) noexcept;
		~image();

		void swap(image& _other) noexcept;

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