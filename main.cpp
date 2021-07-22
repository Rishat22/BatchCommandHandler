#include <iostream>
#include <vector>
#include <string>

enum class TypeCommad{
	DEFAULT,
	OUT,
	WHILE,
	END
};

class BatchCommand{
public:
	BatchCommand(const TypeCommad type, const std::string& arg )
	{
		this->mType = type;
		this->mArg = arg;
	}

	BatchCommand(const TypeCommad type )
	{
		this->mType = type;
	}
	BatchCommand* clone()
	{
		return new BatchCommand( mType, mArg );
	}
	TypeCommad type() const
	{
		return mType;
	}

	std::string arg() const
	{
		return mArg;
	}

private:
	std::string mArg;
	TypeCommad mType = TypeCommad::DEFAULT;
};

class Tokenizer
{
public:
	Tokenizer(const size_t commandsMaxSize)
		: m_CommandsMaxSize(commandsMaxSize)
	{}
	std::vector< BatchCommand* >& Tokenize( const std::vector< std::string >& str_commands ) {

		size_t static_command_counter = 0;
		for( const auto& command : str_commands ) {
			if(command == "{")
			{
				mRetValue.emplace_back( new BatchCommand( TypeCommad::WHILE ) );
				break;
			}
			else if (command == "}")
			{
				mRetValue.emplace_back( new BatchCommand( TypeCommad::END ) );
				break;
			}
			else
			{
				mRetValue.emplace_back( new BatchCommand( TypeCommad::DEFAULT,  command ) );
				if(++static_command_counter == m_CommandsMaxSize)
				{
					mRetValue.emplace_back( new BatchCommand( TypeCommad::OUT ) );
					static_command_counter = 0;
				}
				break;
			}
			}

		return mRetValue;
	}
	void ClearData()
	{
		for (auto it = mRetValue.begin() ; it != mRetValue.end(); ++it)
			if((*it) != nullptr)
				delete (*it);
	}
private:
	size_t m_CommandsMaxSize;
	std::vector< BatchCommand* > mRetValue;
};

class BatchCommandHandler
{
public:
	BatchCommandHandler(const size_t commandsMaxSize)
		: m_CommandsMaxSize(commandsMaxSize)
		, mTokenizer(m_CommandsMaxSize)
	{
		m_StaticCommands.reserve(commandsMaxSize);
	}
	~BatchCommandHandler() = default;
	void Interpret(const std::vector< std::string >& str_commands ){
		Interpret( mTokenizer.Tokenize( str_commands ) );
	}
	void ClearData()
	{
		mTokenizer.ClearData();
	}
private:
	void Interpret(std::vector<BatchCommand*> batch_commands)
	{
		size_t brc = 0; // счетчик незакрытых скобок.
		for( const auto batch_command : batch_commands )
		{
			switch (batch_command->type()){
				case TypeCommad::OUT:
				{
					for(const auto& command_data : m_StaticCommands)
						std::cout << command_data;
					m_StaticCommands.clear();
					break;
				}
				case TypeCommad::WHILE:
				{
					if(!brc++) //Открываем скобку.
					{
						for(const auto& command_data : m_StaticCommands)
							std::cout << command_data;
						m_StaticCommands.clear();
					}
					break;
				}
				case TypeCommad::END:
				{
					if(!brc--)  //Если закрытая инкрементируем счетчик.
					{
						for(const auto& command_data : m_DynamicCommands)
							std::cout << command_data;
						m_DynamicCommands.clear();
					}
					break;
				}
				default:
				{
					if(!brc)  //Если закрытая инкрементируем счетчик.
						m_StaticCommands.push_back(batch_command->arg());
					else
						m_DynamicCommands.push_back(batch_command->arg());
					break;
				}
			}
		}
//		case TypeComad::END:
//		{
//			if(!brc)
//			{
//				//Выводим статический блок
//			}
//			break;
//		}
	}
private:
	size_t m_CommandsMaxSize;
	Tokenizer mTokenizer;
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

	std::string inputData;
	BatchCommandHandler batch_command_handler(commands_max_size);
	std::vector<std::string> str_commands;
	std::string str_command;
	while(std::getline(std::cin, inputData))
	{
		str_commands.push_back(str_command);
	}
	return 0;
}
