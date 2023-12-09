#pragma once

#include <filesystem>
#include <optional>
#include <unordered_set>



namespace engine::util
{
	using std::filesystem::path;

	class file_searcher
	{
	public:

		using dirs_storage_t = std::unordered_set<path>;

		bool addSearchDirectory(path _directory_path) noexcept;
		bool removeSearchDirectory(const path& _directory_path) noexcept;

		std::optional<path> searchFile(const path& _path_to_file) const noexcept;

		const dirs_storage_t& getSearchDirectories() const noexcept;

	private:

		dirs_storage_t m_directories;

	};
}