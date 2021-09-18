#pragma once

#include "CoreMinimal.h"

#include <sstream>
#include <cstdlib>
#include <vector>

class FSystemCommand
{
public:
    FSystemCommand(const char* command = "");
    
    inline const std::vector<std::string>& GetResult() const { return Result; }
    inline bool HasFailed() const { return bFailed; }
    
private:
    std::vector<std::string> Result;
    bool bFailed;
};