#ifndef BATCHCOMMANDHANDLER_H
#define BATCHCOMMANDHANDLER_H
#include <iostream>
#include <string>
#include <vector>
#include "tokenizer.h"

class BatchCommandHandler
{
public:
    BatchCommandHandler(const size_t commandsMaxSize);
    ~BatchCommandHandler() = default;
    void ProcessCommand( const std::string& str_command );
private:
    void ProcessCommand(const std::vector<BatchCommand*>& batch_commands);
    void PrintCommands(const std::vector< std::string > str_commands);
private:
    Tokenizer m_Tokenizer;
    std::vector< std::string > m_StaticCommands;
    std::vector< std::string > m_DynamicCommands;
};

#endif // BATCHCOMMANDHANDLER_H
