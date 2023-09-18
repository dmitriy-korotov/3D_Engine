#include <engine/util/file_reader.hpp>

#include <engine/logging/log.hpp>

#include <fstream>



constexpr size_t BUFFER_SIZE = 4096;



namespace engine::util
{
	file_reader::file_reader(const path& _path_to_file) noexcept
	{
		read(_path_to_file);
	}



	void file_reader::read(const path& _path_to_file) noexcept
	{
		std::ifstream fin(_path_to_file);
		if (fin.is_open())
		{
			m_data.clear();
			std::string buffer(BUFFER_SIZE, '\0');
			while (fin.read(&buffer[0], BUFFER_SIZE))
			{
				m_data.append(buffer, 0, fin.gcount());
			}
			m_data.append(buffer, 0, fin.gcount());
		}
		else
		{
			LOG_ERROR("[File Reader ERROR] Can't open file: {0}", _path_to_file.generic_string());
		}
	}



	std::string& file_reader::getData() noexcept
	{
		return m_data;
	}
}