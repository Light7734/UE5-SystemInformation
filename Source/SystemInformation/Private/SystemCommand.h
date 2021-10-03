#pragma once

#include "CoreMinimal.h"

#include <sstream>
#include <cstdlib>
#include <vector>

class SYSTEMINFORMATION_API FSystemCommand
{
public:
    FSystemCommand(const char* command);
    
    inline const TArray<FString>& GetResult() const { return Result; }
    inline bool HasFailed() const { return bFailed; }

	inline auto begin() const { return Result.begin(); }
	inline auto end() const { return Result.end(); }

private:
    TArray<FString> Result;
    bool bFailed;
};