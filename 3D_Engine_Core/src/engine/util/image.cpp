#include <engine/util/image.hpp>

#include <stb/image.h>



namespace engine::util
{
	image::image(const std::filesystem::path& _path_to_image)
	{
		m_data = reinterpret_cast<std::byte*>(stbi_load(_path_to_image.generic_string().c_str(), &m_width, &m_height, &m_channels, 0));
		if (m_data != nullptr)
		{
			m_is_loaded = true;
		}
	}



	image::image(image&& _other) noexcept
			: m_channels(_other.m_channels)
			, m_data(_other.m_data)
			, m_width(_other.m_width)
			, m_height(_other.m_height)
			, m_is_loaded(_other.m_is_loaded)
	{
		_other.m_channels = 0;
		_other.m_width = 0;
		_other.m_height = 0;
		_other.m_data = nullptr;
		_other.m_is_loaded = false;
	}



	image& image::operator=(image&& _right) noexcept
	{
		image tmp = std::move(_right);
		swap(tmp);
		return *this;
	}



	void image::swap(image& _other) noexcept
	{
		std::swap(m_width, _other.m_width);
		std::swap(m_height, _other.m_height);
		std::swap(m_data, _other.m_data);
		std::swap(m_channels, _other.m_channels);
		std::swap(m_is_loaded, _other.m_is_loaded);
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



	const std::byte* image::getData() const noexcept
	{
		return m_data;
	}



	std::byte* image::getData() noexcept
	{
		return m_data;
	}



	bool image::isLoaded() const noexcept
	{
		return m_is_loaded;
	}



	image::~image()
	{
		if (m_data != nullptr)
		{
			stbi_image_free(m_data);
		}
	}
}