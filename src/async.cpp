#include <memory>
#include <sstream>
#include "async.h"
#include "outputs/console_output.h"
#include "outputs/logfile_output.h"
#include "batch_command_handler.h"

namespace async {

std::unique_ptr<BatchCommandHandler> BATCH_COMMAND_HANDLER = nullptr;

int connect(const std::size_t bulk_size)
{
	if(BATCH_COMMAND_HANDLER == nullptr)
	{
		BATCH_COMMAND_HANDLER.reset( new BatchCommandHandler(bulk_size));
		BATCH_COMMAND_HANDLER->addOutputPrinter( new ConsoleOutput() );
		auto logfile_output = new LogFileOutput();
		logfile_output->startWork();
		BATCH_COMMAND_HANDLER->addOutputPrinter( logfile_output );
	}

	return BATCH_COMMAND_HANDLER->createContext();
}

void receive(const char* data, const std::size_t length, const int /*context*/)
{
	const auto inputData = std::string{data, length};
	std::stringstream ss(inputData);
	std::string command;

	while(std::getline(ss, command, '\n')){
		BATCH_COMMAND_HANDLER->processCommand(inputData);
	}
}

void disconnect(const int context)
{
	if(BATCH_COMMAND_HANDLER->removeContext(context) )
	{
		BATCH_COMMAND_HANDLER.reset();
		std::cout << "No more connections" << std::endl;
	}

}

}
