#include <engine/image.hpp>

#include <stb/image.h>



namespace engine
{
	image::image(const std::filesystem::path& _path_to_image)
	{
		m_data = stbi_load(_path_to_image.generic_string().c_str(), &m_width, &m_height, &m_channels, 0);
		if (m_data != nullptr)
		{
			m_is_loaded = true;
		}
	}



	int image::getWidth() const noexcept
	{
		return m_width;
	}



	int image::getHeight() const noexcept
	{
		return m_height;
	}



	int image::getChannels() const noexcept
	{
		return m_channels;
	}



	const uint8_t* image::getData() const noexcept
	{
		return m_data;
	}



	uint8_t* image::getData() noexcept
	{
		return m_data;
	}



	bool image::isLoaded() const noexcept
	{
		return m_is_loaded;
	}



	image::~image()
	{
		stbi_image_free(m_data);
	}
}