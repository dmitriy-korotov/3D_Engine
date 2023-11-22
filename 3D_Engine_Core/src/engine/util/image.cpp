#include <engine/util/image.hpp>

#include <stb/image.h>



namespace engine::util
{
	image::image(const std::filesystem::path& _path_to_image)
	{
		m_data = reinterpret_cast<std::byte*>(stbi_load(_path_to_image.generic_string().c_str(), &m_width, &m_height, &m_channels, 0));
		if (m_data != nullptr)
			m_is_loaded = true;
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



	auto image::operator=(image&& _right) noexcept -> image&
	{
		image tmp = std::move(_right);
		swap(tmp);
		return *this;
	}



	auto image::swap(image& _other) noexcept -> void
	{
		std::swap(m_width, _other.m_width);
		std::swap(m_height, _other.m_height);
		std::swap(m_data, _other.m_data);
		std::swap(m_channels, _other.m_channels);
		std::swap(m_is_loaded, _other.m_is_loaded);
	}



	auto image::getWidth() const noexcept -> int
	{
		return m_width;
	}



	auto image::getHeight() const noexcept -> int
	{
		return m_height;
	}



	auto image::getChannels() const noexcept -> int
	{
		return m_channels;
	}



	auto image::getData() const noexcept -> const std::byte*
	{
		return m_data;
	}



	auto image::getData() noexcept -> std::byte*
	{
		return m_data;
	}



	auto image::isLoaded() const noexcept -> bool
	{
		return m_is_loaded;
	}



	image::~image()
	{
		if (m_data != nullptr)
			stbi_image_free(m_data);
	}
}