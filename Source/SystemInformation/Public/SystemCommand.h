#pragma once

#include "CoreMinimal.h"

#include <sstream>
#include <cstdlib>
#include <vector>

class SYSTEMINFORMATION_API FSystemCommand
{
public:
    FSystemCommand(const char* command);
    
    inline const std::vector<std::string>& GetResult() const { return Result; }
    inline bool HasFailed() const { return bFailed; }

	inline std::vector<std::string>::const_iterator begin() const { return Result.begin(); }
	inline std::vector<std::string>::const_iterator end() const { return Result.end(); }

private:
    std::vector<std::string> Result;
    bool bFailed;
};