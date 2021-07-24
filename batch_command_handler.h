#ifndef BATCHCOMMANDHANDLER_H
#define BATCHCOMMANDHANDLER_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Output/ioutput.h"
#include "tokenizer.h"

class BatchCommandHandler
{
public:
    BatchCommandHandler(const size_t commandsMaxSize);
    ~BatchCommandHandler() = default;
    void ProcessCommand( const std::string& str_command );
    void AddOutputPrinter( IOutput* output_printer );
private:
    void ProcessCommand(const std::vector<std::unique_ptr<BatchCommand> >& batch_commands);
	void PrintCommands(const std::vector<std::string>& str_commands);
private:
    Tokenizer m_Tokenizer;
    std::vector< std::unique_ptr< IOutput > > m_OutputPrinters;
    std::vector< std::string > m_StaticCommands;
    std::vector< std::string > m_DynamicCommands;
};

#endif // BATCHCOMMANDHANDLER_H
