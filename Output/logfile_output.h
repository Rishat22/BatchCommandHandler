#ifndef LOGFILEOUTPUT_H
#define LOGFILEOUTPUT_H
#include <string>
#include <vector>
#include "ioutput.h"

class LogFileOutput : public IOutput
{
public:
    void print(const std::vector<std::string> str_data) override;
};

#endif // LOGFILEOUTPUT_H
