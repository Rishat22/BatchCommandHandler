#ifndef BATCHCOMMANDHANDLER_H
#define BATCHCOMMANDHANDLER_H
#include <memory>
#include <vector>
#include <string>
#include "icommand.h"

class BatchCommandHandler : public ICommand
{
public:
    BatchCommandHandler() = default;
    ~BatchCommandHandler() = default;

    void addCommand(std::unique_ptr<ICommand> cmd);
    void execute() override;
private:
    std::vector<std::unique_ptr<ICommand>> m_commands;
};

#endif // BATCHCOMMANDHANDLER_H
