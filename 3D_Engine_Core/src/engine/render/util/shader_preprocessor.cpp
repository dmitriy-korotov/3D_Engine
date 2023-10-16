#include <engine/render/util/shader_preprocessor.hpp>

#include <engine/logging/log.hpp>

#include <engine/util/file_reader.hpp>

#include <engine/render/shaders_manager.hpp>



static constexpr size_t INITIAL_SIZE = 4096;
static constexpr std::string_view INCLUDE_PREPROCESSE_COMAND = "include";

static constexpr char OPEN_BRACKET = '<';
static constexpr char CLOSE_BRACKET = '>';



namespace engine::render::utility
{
	shader_preprocessor::shader_preprocessor(const path& _path_to_shader) noexcept
	{
		preprocesse(_path_to_shader);
	}



	shader_preprocessor::shader_preprocessor(const std::string_view& _source) noexcept
	{
		preprocesse(_source);
	}




	void shader_preprocessor::preprocesse(const path& _path_to_shader) noexcept
	{
		auto result = __preprocesse(_path_to_shader);
		if (result.has_value())
		{
			m_is_successfully = true;
			m_preprocessed_data = std::move(result.value());
		}
	}



	void shader_preprocessor::preprocesse(const std::string_view& _source) noexcept
	{
		auto result = __preprocesse(_source);
		if (result.has_value())
		{
			m_is_successfully = true;
			m_preprocessed_data = std::move(result.value());
		}
	}



	bool shader_preprocessor::isIncludeCommand(const std::string_view& _text, size_t& _current_position) noexcept
	{
		if (_text[_current_position] == '#')
		{
			std::string command;

			size_t current_position_copy = _current_position;
			while (current_position_copy + 1 < _text.size() && command.length() < INCLUDE_PREPROCESSE_COMAND.length())
			{
				command.push_back(_text[current_position_copy + 1]);
				current_position_copy++;
			}
			if (command == INCLUDE_PREPROCESSE_COMAND)
			{
				_current_position = current_position_copy;
				return true;
			}
		}
		return false;
	}



	std::optional<std::string> shader_preprocessor::readPath(const std::string_view& _text, size_t& _current_position) noexcept
	{
		std::string path;
		while (_current_position < _text.size())
		{
			if (_text[_current_position] == CLOSE_BRACKET)
				break;

			if (_text[_current_position] == '\n')
			{
				LOG_WARN("[Shader preprocessor WARN] Don't closed bracket (line : {0})");
				return std::nullopt;
			}

			path.push_back(_text[_current_position++]);
		}
		return path;
	}



	std::optional<size_t> shader_preprocessor::findOpenBracket(const std::string_view& _text, size_t _current_position) noexcept
	{
		while (_current_position < _text.size())
		{
			if (_text[_current_position] == OPEN_BRACKET)
				return _current_position;

			if (_text[_current_position] == '\n')
				break;

			_current_position++;
		}
		return std::nullopt;
	}



	std::optional<path> shader_preprocessor::findAbsolutePathToShader(const std::string& _shader_file_name) noexcept
	{
		for (const path& directory : shaders_manager::instance().getShadersDirectories())
		{
			path absolute_path = directory / _shader_file_name;
			if (std::filesystem::exists(absolute_path))
				return absolute_path;
		}
		return std::nullopt;
	}



	std::optional<std::string> shader_preprocessor::__preprocesse(const path& _path_to_shader) noexcept
	{
		if (m_already_processed_files.find(_path_to_shader) != m_already_processed_files.end())
		{
			LOG_WARN("[Shader preprocessor WARN] Double including file '{0}'", _path_to_shader.generic_string());
			return std::nullopt;
		}
		m_already_processed_files.emplace(_path_to_shader);

		util::file_reader reader(_path_to_shader);
		std::string data = std::move(reader.getData());

		return __preprocesse(std::string_view(data));
	}



	std::optional<std::string> shader_preprocessor::__preprocesse(const std::string_view& _source) noexcept
	{
		std::string result;
		result.reserve(INITIAL_SIZE);



		size_t line = 1;
		for (size_t i = 0; i < _source.size(); i++)
		{
			if (_source[i] == '\n')
				line++;

			if (!isIncludeCommand(_source, i))		// isIncludeCommand moved i on end include command
			{										// Example:
				result.push_back(_source[i]);		// Before - #include <path>
				continue;							//			^
			}										// After - #include <path>
													//				   ^


			auto open_bracket_position = findOpenBracket(_source, i);
			if (!open_bracket_position.has_value())
			{
				LOG_ERROR("[Shader preprocessor WARN] Invalid using include directive (line : {0})", line);
				return std::nullopt;
			}



			i = open_bracket_position.value() + 1;
			auto path_to_included_file = readPath(_source, i);	// readPath moved i on close bracket
			if (!path_to_included_file.has_value())
				return std::nullopt;

			auto absolute_path = findAbsolutePathToShader(path_to_included_file.value());
			if (!absolute_path.has_value())
			{
				LOG_ERROR("[Shader preprocessor WARN] Can't find shader file '{0}'", path_to_included_file.value());
				return std::nullopt;
			}

			auto including_file_data = __preprocesse(absolute_path.value());
			if (including_file_data.has_value())
			{
				result.append(including_file_data.value());
			}
			else
			{
				LOG_WARN("[Shader preprocessor WARN] Can't include file '{0}' (line : {2})", path_to_included_file.value(), line);
				return std::nullopt;
			}
		}
		return result;
	}



	bool shader_preprocessor::isSuccessfully() const noexcept
	{
		return m_is_successfully;
	}



	std::string& shader_preprocessor::getResult() noexcept
	{
		return m_preprocessed_data;
	}



	const std::string& shader_preprocessor::getResult() const noexcept
	{
		return m_preprocessed_data;
	}
}