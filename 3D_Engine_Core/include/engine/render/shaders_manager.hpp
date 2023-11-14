#pragma once

#include <engine/util/nocopyeble.hpp>

#include <engine/render/basic_shader_programs_creator.hpp>

#include <engine/util/file_searcher.hpp>

#include <filesystem>
#include <unordered_set>
#include <unordered_map>
#include <optional>



namespace engine::render
{
	using std::filesystem::path;

	class shaders_manager: private util::nocopyeble
	{
	public:

		using dirs_storage_t = util::file_searcher::dirs_storage_t;
		using shader_program_ptr_t = basic_shader_programs_creator::shader_ptrogram_ptr_t;
		using programs_map_t = std::unordered_map<std::string, shader_program_ptr_t>;
		using creator_ptr_t = std::unique_ptr<basic_shader_programs_creator>;



		void setupShaderProgramsCreator(creator_ptr_t _creator) noexcept;

		bool addShadersDirectory(path _directory_path) noexcept;
		bool removeShadersDirectory(const path& _directory_path) noexcept;

		[[nodiscard]] shader_program_ptr_t loadShaderProgram(std::string_view _program_name,
															 const path& _veretx_shader,
															 const path& _fragment_shader) noexcept;

		[[nodiscard]] shader_program_ptr_t getShaderProgram(std::string_view _program_name) const noexcept;
		bool deleleShaderProgram(std::string_view _program_name) noexcept;

		const dirs_storage_t& getShadersDirectories() const noexcept;
		const programs_map_t& getShaderPrograms() const noexcept;

	protected:

		shaders_manager() = default;

		static shaders_manager& instance() noexcept;

	private:

		std::optional<path> searchShader(const path& _path_to_shader) const noexcept;

	private:

		util::file_searcher m_file_searcher;

		creator_ptr_t m_shader_programs_creator = nullptr;
		programs_map_t m_shader_programs;

	};
}