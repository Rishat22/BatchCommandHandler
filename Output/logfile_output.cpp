#include "logfile_output.h"
#include <chrono>
#include <fstream>

//const std::chrono::milliseconds task_process_time(100);

LogFileOutput::LogFileOutput()
	: m_TaskReady(false)
{
}

void LogFileOutput::print(const std::vector<std::string>& str_data)
{
	{
		std::lock_guard lock{m_Mtx};
		m_CmdTasks.push(str_data);
		m_TaskReady = true;
	}
	m_ConditionVar.notify_one();
}

void LogFileOutput::saveData(const std::vector<std::string>& str_data)
{
	std::string file_name = getFileName();
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

std::string LogFileOutput::getFileName()
{
	const auto curr_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string file_name = "bulk" + std::to_string(curr_time) + ".log";
	return file_name;
}

void LogFileOutput::wait_for_task(bool& task_ready)
{
	std::unique_lock lock(m_Mtx);
	m_ConditionVar.wait(lock, [&task_ready]() { return task_ready; });
	task_ready = false;
	lock.unlock();
}

void LogFileOutput::start()
{
	for (auto& thread : m_ProcessingThreads)
	{
		thread = std::thread([&]()
		{
			while (true)
			{
				if (!m_CmdTasks.empty())
				{
					wait_for_task(m_TaskReady);
					saveData(m_CmdTasks.front());
					m_CmdTasks.pop();
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		});
		thread.join();
	}
}

void LogFileOutput::stop()
{

}

