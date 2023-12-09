#include <engine/util/file_searcher.hpp>



namespace engine::util
{
	auto file_searcher::addSearchDirectory(path _directory_path) noexcept -> bool
	{
		return m_directories.emplace(std::move(_directory_path)).second;
	}



	auto file_searcher::removeSearchDirectory(const path& _directory_path) noexcept -> bool
	{
		return (m_directories.erase(_directory_path) > 0);
	}



	auto file_searcher::searchFile(const path& _path_to_file) const noexcept -> std::optional<path>
	{
		for (const path& directory : m_directories)
		{
			path absolute_path = directory / _path_to_file;
			if (std::filesystem::exists(absolute_path))
				return absolute_path;
		}
		return std::nullopt;
	}



	auto file_searcher::getSearchDirectories() const noexcept -> const dirs_storage_t&
	{
		return m_directories;
	}
}