#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>
#include "batch_command.h"

class Tokenizer
{
public:
    Tokenizer(const size_t commandsMaxSize);
    std::vector< BatchCommand* > Tokenize( const std::string& str_command );
private:
    size_t m_CommandsMaxSize;
    size_t m_StaticCommandCounter;
    size_t m_Brc; // счетчик незакрытых скобок.;
};


#endif // TOKENIZER_H
