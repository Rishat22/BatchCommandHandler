#include "console_output.h"
#include <ctime>
#include <iostream>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>

void ConsoleOutput::print(const std::vector<std::string>& str_data)
{
	std::lock_guard lock{m_Mtx};
	m_printData = str_data;
}

void ConsoleOutput::startWork()
{
	m_isWorking = true;
	m_outputThread = std::thread([&]()
	{
		while(m_isWorking)
		{
			if(!m_printData.empty())
			{
				std::lock_guard lock{m_Mtx};
				printToConsole(m_printData);
				m_printData.clear();
			}
		}
	});
}

void ConsoleOutput::printToConsole(const std::vector<std::string>& str_data)
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

void ConsoleOutput::stopWork()
{
	m_isWorking = false;
	if(m_outputThread.joinable())
		m_outputThread.join();
}
