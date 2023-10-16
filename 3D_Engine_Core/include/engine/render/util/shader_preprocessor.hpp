#pragma once

#include <string>
#include <filesystem>
#include <unordered_set>
#include <optional>



namespace engine::render::utility
{
	using std::filesystem::path;

	class shader_preprocessor
	{
	public:

		shader_preprocessor() = default;
		shader_preprocessor(const path& _path_to_shader) noexcept;
		shader_preprocessor(const std::string_view& _source) noexcept;

		void preprocesse(const path& _path_to_shader) noexcept;
		void preprocesse(const std::string_view& _source) noexcept;

		bool isSuccessfully() const noexcept;

		std::string& getResult() noexcept;
		const std::string& getResult() const noexcept;

	private:

		std::optional<std::string> __preprocesse(const path& _path_to_shader) noexcept;
		std::optional<std::string> __preprocesse(const std::string_view& _source) noexcept;
		static bool isIncludeCommand(const std::string_view& _text, size_t& _current_position) noexcept;
		static std::optional<std::string> readPath(const std::string_view& _text, size_t& _current_position) noexcept;
		static std::optional<size_t> findOpenBracket(const std::string_view& _text, size_t _current_position) noexcept;

	private:

		bool m_is_successfully = false;

		std::string m_preprocessed_data;

		std::unordered_set<path> m_already_processed_files;

	};
}