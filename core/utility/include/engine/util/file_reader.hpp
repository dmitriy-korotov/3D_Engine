#pragma once

#include <engine/util/nocopyeble.hpp>

#include <filesystem>



namespace engine::util
{
	using namespace std::filesystem;

	class file_reader: util::nocopyeble
	{
	public:

		file_reader() = default;
		file_reader(const path& _path_to_file) noexcept;

		void read(const path& _path_to_file) noexcept;
		std::string& getData() noexcept;

	private:

		std::string m_data;

	};
}