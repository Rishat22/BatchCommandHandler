#include "batch_command_handler.h"

void BatchCommandHandler::addCommand(std::unique_ptr<ICommand> cmd)
{
	m_commands.emplace_back(std::move(cmd));
}

void BatchCommandHandler::execute()
{
	for (auto& cmd : m_commands)
		cmd->execute();
}
