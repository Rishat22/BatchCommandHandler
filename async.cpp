#include "async.h"
#include <memory>
#include "Output/console_output.h"
#include "Output/logfile_output.h"
#include "batch_command_handler.h"

namespace async {

std::unique_ptr<BatchCommandHandler> BATCH_COMMAND_HANDLER = nullptr;

int connect(const std::size_t bulk_size)
{

	BATCH_COMMAND_HANDLER.reset( new BatchCommandHandler(bulk_size));

	BatchCommandHandler batch_command_handler(bulk_size);
	batch_command_handler.AddOutputPrinter( new ConsoleOutput() );
	batch_command_handler.AddOutputPrinter( new LogFileOutput() );
}

void receive(const char* /*data*/, const std::size_t /*size*/, const int /*context*/)
{
//	BATCH_COMMAND_HANDLER->ProcessCommand(inputData);
}

void disconnect(const int /*context*/)
{
	BATCH_COMMAND_HANDLER.reset();
}

}
