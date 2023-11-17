#pragma once

#include <engine/ecs/components/basic_component.hpp>

#include <engine/render/render.hpp>
#include <engine/render/fwd/basic_shader_program.hpp>

#include <memory>



namespace engine::ecs::components
{
	using namespace render;

	class renderable: public virtual basic_component
	{
	public:

		static constexpr std::string_view component_name = "renderable";



		using shader_program_ptr_t = std::shared_ptr<basic_shader_program>;

		renderable() = default;
		renderable(std::string_view _shader_program_name, DrawingMode _drawing_mode = DrawingMode::Triangle) noexcept;

		bool setShaderProgram(std::string_view _shader_program_name) noexcept;
		const shader_program_ptr_t& getShaderProgram() const noexcept;
		
		void setDrawingMode(DrawingMode _drawing_mode) noexcept;
		DrawingMode getDrawingMode() const noexcept;

		bool putOnUI() noexcept override;

		serialized_view_t serialize() const noexcept override;
		void deserializeFrom(const serialized_view_t& _serialized_view) noexcept override;

	private:

		std::string m_shader_program_name;
		shader_program_ptr_t m_shader_program = nullptr;
		DrawingMode m_drawing_mode = DrawingMode::Triangle;

	};
}