#pragma once

#include <string>

#define INFO_STR_UNKNOWN "N/A"
#define INFO_B_TO_GB(bytes) bytes / 1000000.0 / 1000.0

namespace HardwareInfo {

	static const char* ConvertBytesToGigabytes(const std::string& bytes)
	{ 
		try 
		{
			return (std::to_string(std::stoull(bytes) / 1000000.0 / 1000.0) + " gb").c_str();
		}
		catch(std::exception e)
		{
			(void)e;
			UE_LOG(LogTemp, Error, TEXT("Failed to convert bytes to gigabytes: %s"), *FString(bytes.c_str()));
			return INFO_STR_UNKNOWN;
		}
	}

}