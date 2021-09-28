#include "logfile_output.h"
#include <chrono>
#include <fstream>
#include <sstream>
#include <random>
#include <filesystem>

namespace fs = std::filesystem;

LogFileOutput::LogFileOutput()
	: m_TaskReady(false)
	, m_isWorking(false)
{
}

LogFileOutput::~LogFileOutput()
{
	stopWork();
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

fs::path getLogDir()
{
	const fs::path log_path = fs::current_path() / "logs";
	fs::directory_entry entry_dir { log_path };
	if (!entry_dir.exists())
		fs::create_directory(log_path);
	return log_path;
}

void LogFileOutput::saveData(const std::vector<std::string>& str_data)
{
	const auto file_name = getLogDir() / getFileName();
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
	std::ostringstream filename_stream;
	const auto curr_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	filename_stream << "bulk" << curr_time;

	std::random_device r;
	std::seed_seq seed1{r()};
	std::mt19937 e(seed1);
	std::uniform_int_distribution<int> uniform_dist(0, 100);
	std::normal_distribution<> normal_dist(uniform_dist(e), 2);
	filename_stream << "_" << std::round(normal_dist(e)) << ".log";
	return filename_stream.str();
}

void LogFileOutput::saveTaskData(const bool& is_working, bool& task_ready)
{
	std::unique_lock lock(m_Mtx);
	m_ConditionVar.wait(lock, [&task_ready, &is_working]() { return task_ready || !is_working; });
	if(!m_CmdTasks.empty())
	{
		const auto task_data = m_CmdTasks.front();
		m_CmdTasks.pop();
		task_ready = false;
		saveData(task_data);
	}
}

void LogFileOutput::startWork()
{
	std::unique_lock lock(m_Mtx);
	if(m_isWorking == false)
	{
		m_isWorking = true;
		for (auto& thread : m_ProcessingThreads)
		{
			thread = std::thread([&]()
			{
				while (m_isWorking || !m_CmdTasks.empty())
				{
					saveTaskData(m_isWorking, m_TaskReady);
				}
			});
		}
	}
}

void LogFileOutput::stopWork()
{
	if(m_isWorking)
	{
		{
			std::unique_lock lock(m_Mtx);
			m_isWorking = false;
		}
		m_ConditionVar.notify_all();
		for (auto& thread : m_ProcessingThreads)
		{
			if(thread.joinable())
			{
				thread.join();
			}
		}
	}
}

