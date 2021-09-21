#pragma once

#include "InfoBase.h"
#include "SystemCommand.h"

#include <vector>

struct FOSInformation
{
    std::string Name = UNDETECTED_INFO_STR;
    std::string Manufacturer = UNDETECTED_INFO_STR;
	std::string Architecture = UNDETECTED_INFO_STR;
	std::string Caption = UNDETECTED_INFO_STR;
	std::string Version = UNDETECTED_INFO_STR;
	std::string CurrentUser = UNDETECTED_INFO_STR;
	std::string InstallDate = UNDETECTED_INFO_STR;
	std::string BuildNumber = UNDETECTED_INFO_STR;
	std::string LastBootUpTime = UNDETECTED_INFO_STR;
	std::string BootDevice = UNDETECTED_INFO_STR;
	std::string SerialNumber = UNDETECTED_INFO_STR;
	std::string TotalVirtualMemory = UNDETECTED_INFO_STR;
	std::string TotalVisibleMemory = UNDETECTED_INFO_STR;
	std::string TotalSwapSize = UNDETECTED_INFO_STR;
	std::string FreePhysicalMemory = UNDETECTED_INFO_STR;
	std::string FreeVirtualMemory = UNDETECTED_INFO_STR;

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