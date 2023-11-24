#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/render/basic_renderer.hpp>

#include <memory>



namespace engine::render
{
	class application_renderer: private util::nocopyeble
	{
	public:

		using renderer_ptr_t = std::shared_ptr<basic_renderer>;

		static application_renderer& instance() noexcept;

		void setupRenderer(renderer_ptr_t _renderer) noexcept;
		const renderer_ptr_t& getRenderer() const noexcept;

	private:

		application_renderer() = default;

	private:

		renderer_ptr_t m_renderer = nullptr;

	};
}