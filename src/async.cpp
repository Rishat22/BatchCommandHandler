#include <memory>
#include <sstream>
#include <map>
#include <ctime>
#include "async.h"
#include "outputs/console_output.h"
#include "outputs/logfile_output.h"
#include "batch_command_handler.h"

namespace async {

std::map<int, std::unique_ptr<BatchCommandHandler>> BATCH_COMMAND_HANDLER_LIST;

int createContext()
{
	std::srand(std::time(nullptr));
	int random_variable = std::rand();
	return random_variable;
}

int connect(const std::size_t bulk_size)
{
	auto batchCommandHandler = std::make_unique<BatchCommandHandler>(bulk_size);
	batchCommandHandler->addOutputPrinter( new ConsoleOutput() );
	auto logfile_output = new LogFileOutput();
	logfile_output->startWork();
	batchCommandHandler->addOutputPrinter( logfile_output );

	auto context = createContext();
	BATCH_COMMAND_HANDLER_LIST[context] = std::move(batchCommandHandler);
	return context;
}

void receive(const char* data, const std::size_t length, const int context)
{
	const auto inputData = std::string{data, length};
	std::stringstream ss(inputData);
	std::string command;

	while(std::getline(ss, command, '\n')){
		BATCH_COMMAND_HANDLER_LIST[context]->processCommand(inputData);
	}
}

void disconnect(const int context)
{
	if(BATCH_COMMAND_HANDLER_LIST.find(context) != BATCH_COMMAND_HANDLER_LIST.end() )
	{
		BATCH_COMMAND_HANDLER_LIST.erase(context);
	}

	if(BATCH_COMMAND_HANDLER_LIST.empty())
		std::cout << "No more connections" << std::endl;
}

}
