#include "batch_command_handler.h"


BatchCommandHandler::BatchCommandHandler(const size_t commandsMaxSize)
	: m_Tokenizer(commandsMaxSize)
{
	m_StaticCommands.reserve(commandsMaxSize);
}

void BatchCommandHandler::ProcessCommand(const std::string& str_command){
	ProcessCommand( m_Tokenizer.Tokenize( str_command ) );
}

void BatchCommandHandler::AddOutputPrinter(IOutput* output_printer)
{
	m_OutputPrinters.push_back( output_printer );
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
				m_StaticCommands.emplace_back(batch_command->arg());
				break;
			}
			case TypeCommad::ADD_DYNAMIC:
			{
				m_DynamicCommands.emplace_back(batch_command->arg());
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
	for(const auto output_printer : m_OutputPrinters)
	{
		output_printer->print(str_commands);
	}
}
