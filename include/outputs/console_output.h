#ifndef CONSOLEOUTPUT_H
#define CONSOLEOUTPUT_H
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include "ioutput.h"

class ConsoleOutput : public IOutput
{
public:
	ConsoleOutput() = default;
	virtual ~ConsoleOutput() = default;
	void print(const std::vector<std::string>& str_data) override;
	void startWork() override;
	void stopWork() override;
private:
	void printToConsole(const std::vector<std::string>& str_data);
private:
	std::thread m_outputThread;
	std::vector<std::string> m_printData;
	bool m_isWorking;
	std::mutex m_Mtx;
};

#endif // CONSOLEOUTPUT_H
