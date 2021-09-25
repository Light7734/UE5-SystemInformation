#pragma once

#include "InfoBase.h"

#include <vector>

struct FOSInformation
{
    std::string Name = INFO_STR_UNKNOWN;
    std::string Manufacturer = INFO_STR_UNKNOWN;
	std::string Architecture = INFO_STR_UNKNOWN;
	std::string Caption = INFO_STR_UNKNOWN;
	std::string Version = INFO_STR_UNKNOWN;
	std::string CurrentUser = INFO_STR_UNKNOWN;
	std::string InstallDate = INFO_STR_UNKNOWN;
	std::string BuildNumber = INFO_STR_UNKNOWN;
	std::string LastBootUpTime = INFO_STR_UNKNOWN;
	std::string BootDevice = INFO_STR_UNKNOWN;
	std::string SerialNumber = INFO_STR_UNKNOWN;
	std::string TotalVirtualMemory = INFO_STR_UNKNOWN;
	std::string TotalVisibleMemory = INFO_STR_UNKNOWN;
	std::string TotalSwapSize = INFO_STR_UNKNOWN;
	std::string FreePhysicalMemory = INFO_STR_UNKNOWN;
	std::string FreeVirtualMemory = INFO_STR_UNKNOWN;

	int Index;
};

class FOSInfoCollector
{
public:
	FOSInfoCollector();

	inline const std::vector<FOSInformation>& GetOSInformation() const { return OSsInformation; }
	inline uint8_t GetOSCount() const { return OSCount; }

private:
	std::vector<FOSInformation> OSsInformation;
	uint8_t OSCount;
};