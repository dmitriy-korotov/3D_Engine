#include <engine/render/shaders_manager.hpp>

#include <engine/logging/log.hpp>

#include <engine/util/file_reader.hpp>

#include <cassert>



namespace engine::render
{
	shaders_manager& shaders_manager::instance() noexcept
	{
		static shaders_manager instance;
		return instance;
	}





	void shaders_manager::setupShaderProgramsCreator(creator_ptr_t _creator) noexcept
	{
		m_shader_programs_creator = std::move(_creator);
	}



	void shaders_manager::addShadersDirectory(path _directory_path) noexcept
	{
		m_shaders_directories.emplace(std::move(_directory_path));
	}



	void shaders_manager::removeShadersDirectory(const path& _directory_path) noexcept
	{
		m_shaders_directories.erase(_directory_path);
	}



	std::optional<path> shaders_manager::searchShader(const path& _path_to_shader) const noexcept
	{
		for (const path& shaders_directory : m_shaders_directories)
		{
			path absolute_path = shaders_directory / _path_to_shader;
			if (std::filesystem::exists(absolute_path))
				return absolute_path;
		}
		return std::nullopt;
	}



	shaders_manager::shader_program_ptr_t shaders_manager::loadShaderProgram(std::string_view _program_name,
																			 const path& _veretx_shader,
																			 const path& _fragment_shader) noexcept
	{
		assert(m_shader_programs_creator != nullptr);



		auto path_to_vertex_shader = searchShader(_veretx_shader);
		if (!path_to_vertex_shader.has_value())
		{
			LOG_ERROR("[Shaders manager ERROR] Can't find vertex shader with this filename: '{0}'", _veretx_shader.generic_string());
			return nullptr;
		}

		auto path_to_fragment_shader = searchShader(_fragment_shader);
		if (!path_to_fragment_shader.has_value())
		{
			LOG_ERROR("[Shaders manager ERROR] Can't find fragment shader with this filename: '{0}'", _fragment_shader.generic_string());
			return nullptr;
		}

		util::file_reader vs_reader(path_to_vertex_shader.value());
		util::file_reader fs_reader(path_to_fragment_shader.value());

		auto shader_program = m_shader_programs_creator->createShaderProgram(std::move(vs_reader.getData()), std::move(fs_reader.getData()));

		auto result = m_shader_programs.emplace(_program_name, std::move(shader_program));
		if (result.second == false)
		{
			LOG_ERROR("[Shaders manager ERROR] Can't add shader program with this name: '{0}'", _program_name);
			return nullptr;
		}

		return result.first->second;
	}



	shaders_manager::shader_program_ptr_t shaders_manager::getShaderProgram(std::string_view _program_name) const noexcept
	{
		auto finded_program = m_shader_programs.find(_program_name.data());
		if (finded_program == m_shader_programs.end())
		{
			LOG_ERROR("[Shaders manager ERROR] Can't find shader program with this name: '{0}'", _program_name);
			return nullptr;
		}
		return finded_program->second;
	}



	bool shaders_manager::deleleShaderProgram(std::string_view _program_name) noexcept
	{
		auto count_removed_elements = m_shader_programs.erase(_program_name.data());
		return count_removed_elements;
	}



	const shaders_manager::dirs_storage_t& shaders_manager::getShadersDirectories() const noexcept
	{
		return m_shaders_directories;
	}



	const shaders_manager::programs_map_t& shaders_manager::getShaderPrograms() const noexcept
	{
		return m_shader_programs;
	}
}