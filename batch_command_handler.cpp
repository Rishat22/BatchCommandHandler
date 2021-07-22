#include "batch_command_handler.h"


BatchCommandHandler::BatchCommandHandler(const size_t commandsMaxSize)
	: m_Tokenizer(commandsMaxSize)
{
	m_StaticCommands.reserve(commandsMaxSize);
}

void BatchCommandHandler::ProcessCommand(const std::string& str_command){
	ProcessCommand( m_Tokenizer.Tokenize( str_command ) );
}

void BatchCommandHandler::ProcessCommand(const std::vector<BatchCommand*>& batch_commands)
{
	for( const auto batch_command : batch_commands )
	{
		switch (batch_command->type()){
			case TypeCommad::OUT_STATIC:
			{
				PrintCommands(m_StaticCommands);
				m_StaticCommands.clear();
				break;
			}
			case TypeCommad::OUT_DYNAMIC:
			{
				PrintCommands(m_DynamicCommands);
				m_StaticCommands.clear();
				break;
			}
			case TypeCommad::ADD_STATIC:
			{
				m_StaticCommands.push_back(batch_command->arg()); //ToDo mb emplace_back
				break;
			}
			case TypeCommad::ADD_DYNAMIC:
			{
				m_DynamicCommands.push_back(batch_command->arg());
				break;
			}
			default: break;
		}
	}
}

void BatchCommandHandler::PrintCommands(const std::vector<std::string> str_commands)
{
	if( str_commands.empty() )
		return;
	std::cout << "bulk: ";
	size_t index = 0;
	for(const auto& command_data : str_commands)
	{
		std::cout << command_data;
		if(++index < str_commands.size())
			std::cout << ", ";
	}
	std::cout << std::endl;
}
