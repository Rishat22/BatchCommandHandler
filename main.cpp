#include <iostream>
#include <string>
#include "async.h"

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

	async::connect(commands_max_size);
	std::string inputData;
	while(std::getline(std::cin, inputData))
	{
		async::receive(inputData.c_str(), inputData.size(), 0);
	}
	async::disconnect(0);
	return 0;
}
