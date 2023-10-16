#include <engine/render/util/shader_preprocessor.hpp>

#include <engine/logging/log.hpp>

#include <engine/util/file_reader.hpp>



static constexpr size_t INITIAL_SIZE = 4096;
static constexpr std::string_view INCLUDE_PREPROCESSE_COMAND = "include";

static constexpr char OPEN_BRACKET = '<';
static constexpr char CLOSE_BRACKET = '>';



namespace engine::render::utility
{
	void shader_preprocessor::preprocesse(const path& _path_to_shader) noexcept
	{
		auto result = __preprocesse(_path_to_shader);
		if (result.has_value())
		{
			m_is_successfully = true;
			m_preprocessed_data = std::move(result.value());
		}
	}



	bool shader_preprocessor::isIncludeCommand(const std::string& _text, size_t& _current_position) noexcept
	{
		if (_text[_current_position] == '#')
		{
			std::string command;

			while (_current_position + 1 < _text.size() && command.length() < INCLUDE_PREPROCESSE_COMAND.length())
			{
				command.push_back(_text[_current_position + 1]);
				_current_position++;
			}
			return command == INCLUDE_PREPROCESSE_COMAND;
		}
		return false;
	}



	std::optional<std::string> shader_preprocessor::readPath(const std::string& _text, size_t& _current_position) noexcept
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

			path.push_back(_text[_current_position]);
		}
		return path;
	}



	std::optional<size_t> shader_preprocessor::findOpenBracket(const std::string& _text, size_t _current_position) noexcept
	{
		while (_current_position < _text.size())
		{
			if (_text[_current_position] == OPEN_BRACKET)
				return _current_position;

			if (_text[_current_position] == '\n')
				break;
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



		std::string result;
		result.reserve(INITIAL_SIZE);



		size_t line = 1;
		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i] == '\n')
				line++;

			if (!isIncludeCommand(data, i))		// isIncludeCommand moved i on end include command
			{									// Example:
				result.push_back(data[i]);		// Before - #include <path>
				continue;						//			^
			}									// After - #include <path>
												//				   ^


			auto open_bracket_position = findOpenBracket(data, i);
			if (!open_bracket_position.has_value())
			{
				LOG_ERROR("[Shader preprocessor WARN] Invalid using include directive (line : {0})", line);
				return std::nullopt;
			}



			i = open_bracket_position.value() + 1;
			auto path = readPath(data, i);	// readPath moved i on close bracket
			if (!path.has_value())
				return std::nullopt;

			auto including_file_data = __preprocesse(std::move(path.value()));
			if (including_file_data.has_value())
			{
				result.append(including_file_data.value());
			}
			else
			{
				LOG_WARN("[Shader preprocessor WARN] Can't include file '{0}' (line : {2})", path.value(), line);
				return std::nullopt;
			}
		}
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