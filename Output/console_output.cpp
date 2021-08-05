#include "console_output.h"
#include <iostream>

void ConsoleOutput::print(const std::vector<std::string> str_data)
{
	std::cout << "bulk: ";
	size_t index = 0;
	for(const auto& command_data : str_data)
	{
		std::cout << command_data;
		if(++index < str_data.size())
			std::cout << ", ";
	}
	std::cout << std::endl;
}
