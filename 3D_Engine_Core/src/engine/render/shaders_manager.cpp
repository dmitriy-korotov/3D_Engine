#include <engine/render/shaders_manager.hpp>

#include <engine/logging/log.hpp>

#include <engine/util/file_reader.hpp>

#include <cassert>



namespace engine::render
{
	shaders_manager::program_location::program_location(path _vertex_location, path _fragment_location) noexcept
			: m_vertex_location(std::move(_vertex_location))
			, m_fragment_location(std::move(_fragment_location))
	{ }

	void shaders_manager::program_location::setVertexLocation(path _vertex_location) noexcept
	{
		m_vertex_location = std::move(_vertex_location);
	}

	void shaders_manager::program_location::setFragmentLocation(path _fragment_location) noexcept
	{
		m_fragment_location = std::move(_fragment_location);
	}

	const path& shaders_manager::program_location::getVertexLocation() const noexcept
	{
		return m_vertex_location;
	}

	const path& shaders_manager::program_location::getFragmentLocation() const noexcept
	{
		return m_fragment_location;
	}





	shaders_manager& shaders_manager::instance() noexcept
	{
		static shaders_manager instance;
		return instance;
	}





	void shaders_manager::setupShaderProgramsCreator(creator_ptr_t _creator) noexcept
	{
		m_shader_programs_creator = std::move(_creator);
	}



	bool shaders_manager::addShadersDirectory(path _directory_path) noexcept
	{
		return m_file_searcher.addSearchDirectory(std::move(_directory_path));
	}



	bool shaders_manager::removeShadersDirectory(const path& _directory_path) noexcept
	{
		return m_file_searcher.removeSearchDirectory(_directory_path);
	}



	std::optional<path> shaders_manager::searchShader(const path& _path_to_shader) const noexcept
	{
		return m_file_searcher.searchFile(_path_to_shader);
	}



	shaders_manager::shader_program_ptr_t shaders_manager::loadShaderProgram(std::string_view _program_name,
																			 const path& _veretx_shader,
																			 const path& _fragment_shader) noexcept
	{
		assert(m_shader_programs_creator != nullptr);


		auto exists_shader_program = getShaderProgram(_program_name);
		if (exists_shader_program != nullptr)
			return exists_shader_program;


		path path_to_vertex_shader;
		path path_to_fragment_shader;



		if (std::filesystem::exists(_veretx_shader))
		{
			path_to_vertex_shader = _veretx_shader;
		}
		else
		{
			auto path_to_vertex_shader_opt = searchShader(_veretx_shader);
			if (!path_to_vertex_shader_opt.has_value())
			{
				LOG_ERROR("[Shaders manager ERROR] Can't find vertex shader with this filename: '{0}'", _veretx_shader.generic_string());
				return nullptr;
			}
			path_to_vertex_shader = std::move(path_to_vertex_shader_opt.value());
		}

		if (std::filesystem::exists(_fragment_shader))
		{
			path_to_fragment_shader = _fragment_shader;
		}
		else
		{
			auto path_to_fragment_shader_opt = searchShader(_fragment_shader);
			if (!path_to_fragment_shader_opt.has_value())
			{
				LOG_ERROR("[Shaders manager ERROR] Can't find fragment shader with this filename: '{0}'", _fragment_shader.generic_string());
				return nullptr;
			}
			path_to_fragment_shader = std::move(path_to_fragment_shader_opt.value());
		}



		util::file_reader vs_reader(path_to_vertex_shader);
		util::file_reader fs_reader(path_to_fragment_shader);

		auto shader_program = m_shader_programs_creator->createShaderProgram(std::move(vs_reader.getData()), std::move(fs_reader.getData()));

		auto result = m_shader_programs.emplace(_program_name, std::make_pair(shader_program, program_location(_veretx_shader, _fragment_shader)));
		if (result.second == false)
		{
			LOG_ERROR("[Shaders manager ERROR] Can't add shader program with this name: '{0}'", _program_name);
			return nullptr;
		}

		return result.first->second.first;
	}



	shaders_manager::shader_program_ptr_t shaders_manager::getShaderProgram(std::string_view _program_name) const noexcept
	{
		auto finded_program = m_shader_programs.find(_program_name.data());
		if (finded_program == m_shader_programs.end())
			return nullptr;
		return finded_program->second.first;
	}



	auto shaders_manager::getProgramLocation(std::string_view _program_name) const noexcept -> std::optional<program_location>
	{
		auto finded_program = m_shader_programs.find(_program_name.data());
		if (finded_program == m_shader_programs.end())
		{
			LOG_ERROR("[Shaders manager ERROR] Can't find location shader program with this name: '{0}'", _program_name);
			return std::nullopt;
		}
		return finded_program->second.second;
	}



	bool shaders_manager::deleleShaderProgram(std::string_view _program_name) noexcept
	{
		auto count_removed_elements = m_shader_programs.erase(_program_name.data());
		return count_removed_elements;
	}



	const shaders_manager::dirs_storage_t& shaders_manager::getShadersDirectories() const noexcept
	{
		return m_file_searcher.getSearchDirectories();
	}



	const shaders_manager::programs_map_t& shaders_manager::getShaderPrograms() const noexcept
	{
		return m_shader_programs;
	}
}