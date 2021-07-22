#include <iostream>
#include <vector>
#include <string>

enum class TypeCommad{
	DEFAULT,
	OUT_STATIC,
	OUT_DYNAMIC,
	WHILE,
	END
};

class BatchCommand{
public:
	BatchCommand(const TypeCommad type, const std::string& arg )
	{
		this->m_Type = type;
		this->m_Arg = arg;
	}

	BatchCommand(const TypeCommad type )
	{
		this->m_Type = type;
	}
	BatchCommand* clone()
	{
		return new BatchCommand( m_Type, m_Arg );
	}
	TypeCommad type() const
	{
		return m_Type;
	}

	std::string arg() const
	{
		return m_Arg;
	}

private:
	std::string m_Arg;
	TypeCommad m_Type = TypeCommad::DEFAULT;
};

class Tokenizer
{
public:
	Tokenizer() = default;
	BatchCommand* Tokenize( const std::string& str_command ) {
		BatchCommand* result_command = nullptr;
		if(str_command == "{")
		{
			result_command =  new BatchCommand( TypeCommad::WHILE );
		}
		else if (str_command == "}")
		{
			result_command = new BatchCommand( TypeCommad::END );
		}
		else
		{
			result_command = new BatchCommand( TypeCommad::DEFAULT,  str_command );
		}

		return result_command;
	}
};

class BatchCommandHandler
{
public:
	BatchCommandHandler(const size_t commandsMaxSize)
		: m_CommandsMaxSize(commandsMaxSize)
	{
		m_StaticCommands.reserve(commandsMaxSize);
	}
	~BatchCommandHandler() = default;
	void ProcessCommand( const std::string& str_command ){
		ProcessCommand( m_Tokenizer.Tokenize( str_command ) );
	}
private:
	void ProcessCommand(BatchCommand* batch_command)
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
			case TypeCommad::WHILE:
			{
				if(!m_Brc++) //Открываем скобку.
				{
					PrintCommands(m_StaticCommands);
					m_StaticCommands.clear();
				}
				break;
			}
			case TypeCommad::END:
			{
				if(!--m_Brc)  //Если закрытая инкрементируем счетчик.
				{
					PrintCommands(m_DynamicCommands);
					m_DynamicCommands.clear();
				}
				break;
			}
			default:
			{
				if(!m_Brc)  //Если закрытая инкрементируем счетчик.
					m_StaticCommands.push_back(batch_command->arg());
				else
					m_DynamicCommands.push_back(batch_command->arg());

				if(m_StaticCommands.size() == m_CommandsMaxSize)
				{
					PrintCommands(m_StaticCommands);
					m_StaticCommands.clear();
				}
				break;
			}
		}
	}
private:
	void PrintCommands(const std::vector< std::string > str_commands)
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
private:
	size_t m_CommandsMaxSize;
	size_t m_Brc = 0; // счетчик незакрытых скобок.;
	Tokenizer m_Tokenizer;
	std::vector< std::string > m_StaticCommands;
	std::vector< std::string > m_DynamicCommands;
};
int main(int argc, char* argv[])
{
	size_t commands_max_size;
	if (argc != 2)
	{
		std::cout << "Try with the argument: max size commands" << std::endl;
		return 1;
	}
	try
	{
		commands_max_size = std::stoi(argv[1]);
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument: " << ia.what() << '\n';
		return 1;
	}

	BatchCommandHandler batch_command_handler(commands_max_size);
	std::string inputData;
	while(std::getline(std::cin, inputData))
	{
		batch_command_handler.ProcessCommand(inputData);
	}
	return 0;
}
