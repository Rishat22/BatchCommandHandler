#include "logfile_output.h"
#include <chrono>
#include <fstream>


void LogFileOutput::print(const std::vector<std::string> str_data)
{
	const auto curr_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string file_name = "bulk" + std::to_string(curr_time) + ".log";

	std::ofstream log_file;
	log_file.open(file_name);

	log_file << "bulk: ";
	size_t index = 0;
	for(const auto& command_data : str_data)
	{
		log_file << command_data;
		if(++index < str_data.size())
			log_file << ", ";
	}
	log_file << std::endl;
	log_file.close();
}
