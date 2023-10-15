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



		using shader_program_ptr = std::shared_ptr<basic_shader_program>;

		renderable(shader_program_ptr _shader_program, DrawingMode _drawing_mode = DrawingMode::Triangle) noexcept;

		void setShaderProgram(shader_program_ptr _shader_program) noexcept;
		const shader_program_ptr& getShaderProgram() const noexcept;
		
		void setDrawingMode(DrawingMode _drawing_mode) noexcept;
		DrawingMode getDrawingMode() const noexcept;

		bool putOnUI() noexcept override;

	private:

		shader_program_ptr m_shader_program = nullptr;
		DrawingMode m_drawing_mode = DrawingMode::Triangle;

	};
}