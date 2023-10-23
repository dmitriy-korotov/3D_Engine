#pragma once

#include <engine/render/basic_shader_programs_creator.hpp>

#include <filesystem>
#include <unordered_set>
#include <unordered_map>
#include <optional>



namespace engine::render
{
	using std::filesystem::path;

	class shaders_manager
	{
	public:

		using dirs_storage_t = std::unordered_set<path>;
		using shader_program_ptr_t = basic_shader_programs_creator::shader_ptrogram_ptr_t;
		using programs_map_t = std::unordered_map<std::string, shader_program_ptr_t>;
		using creator_ptr_t = std::unique_ptr<basic_shader_programs_creator>;



		static shaders_manager& instance() noexcept;



		void setupShaderProgramsCreator(creator_ptr_t _creator) noexcept;

		void addShadersDirectory(path _directory_path) noexcept;
		void removeShadersDirectory(const path& _directory_path) noexcept;

		[[nodiscard]] shader_program_ptr_t loadShaderProgram(std::string_view _program_name,
															 const path& _veretx_shader,
															 const path& _fragment_shader) noexcept;

		[[nodiscard]] shader_program_ptr_t getShaderProgram(std::string_view _program_name) const noexcept;
		bool deleleShaderProgram(std::string_view _program_name) noexcept;

		const dirs_storage_t& getShadersDirectories() const noexcept;
		const programs_map_t& getShaderPrograms() const noexcept;

	protected:

		shaders_manager() = default;

	private:

		std::optional<path> searchShader(const path& _path_to_shader) const noexcept;

	private:

		 dirs_storage_t m_shaders_directories;

		 creator_ptr_t m_shader_programs_creator = nullptr;
		 programs_map_t m_shader_programs;

	};
}