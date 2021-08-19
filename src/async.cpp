#include <memory>
#include <sstream>
#include "async.h"
#include "outputs/console_output.h"
#include "outputs/logfile_output.h"
#include "batch_command_handler.h"

namespace async {

template <typename T, typename... Args> class Singleton
{
public:
	static T& Instance()
	{
		static T Instance(m_Arg);
		return Instance;
	}
	static void setArgs(const size_t arg)
	{
		m_Arg = arg;
	}
protected:
	Singleton() = default;
	virtual ~Singleton() = default;
private:
	Singleton(const T&);
	Singleton& operator=(const T&);
private:
	static size_t m_Arg;
};


int connect(const std::size_t bulk_size)
{
	Singleton<BatchCommandHandler>::setArgs(bulk_size);
	auto batch_command_handler = Singleton<BatchCommandHandler>::Instance();
	batch_command_handler.addOutputPrinter( new ConsoleOutput() );
	auto logfile_output = new LogFileOutput();
	logfile_output->startWork();
	batch_command_handler.addOutputPrinter( logfile_output );

	return batch_command_handler.createContext();
}

void receive(const char* data, const std::size_t length, const int /*context*/)
{
	const auto inputData = std::string{data, length};
	std::stringstream ss(inputData);
	std::string command;

	auto batch_command_handler = Singleton<BatchCommandHandler>::Instance();
	while(std::getline(ss, command, '\n')){
		batch_command_handler.processCommand(command);
	}
}

void disconnect(const int context)
{
	auto batch_command_handler = Singleton<BatchCommandHandler>::Instance();
	if(batch_command_handler.removeContext(context) )
		std::cout << "No more connections" << std::endl;
}

}
