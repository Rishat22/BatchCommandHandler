#include <iostream>
#include <string>
#include "batch_command_handler.h"

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
