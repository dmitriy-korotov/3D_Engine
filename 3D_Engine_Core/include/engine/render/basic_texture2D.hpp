#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/render/texture_parametrs.hpp>

#include <iostream>



namespace engine::render
{
	class basic_texture2D: private util::nocopyeble
	{
	public:

		basic_texture2D() = default;
		basic_texture2D(basic_texture2D&& _other) noexcept;
		basic_texture2D& operator=(basic_texture2D&& _right) noexcept;
		virtual ~basic_texture2D() = default;

		uint16_t getWidth() const noexcept;
		uint16_t getHeight() const noexcept;

		virtual void setData(const std::byte* _data, uint16_t _width, uint16_t _height,
							 InternalFormat _internal_format = InternalFormat::RGB_8) noexcept = 0;
		virtual void setParametrs(const TextureParamsStorage& _texture_params) noexcept = 0;

		InternalFormat getInternalFormat() const noexcept;
		Wrap getWrapT() const noexcept;
		Wrap getWrapS() const noexcept;
		Filter getMinFilter() const noexcept;
		Filter getMagFilter() const noexcept;

	protected:

		uint16_t m_width = 0;
		uint16_t m_height = 0;

		TextureParamsStorage m_texture_parametrs;
		InternalFormat m_internal_format;

	};
}