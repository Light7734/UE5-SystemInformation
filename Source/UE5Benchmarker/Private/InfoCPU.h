#pragma once

#include "InfoBase.h"

#include <vector>

struct FCPUInfo
{
    std::string Name;
    std::string Manufacturer;
    std::string CoreCount;
    std::string Architecture;
    std::string L2CacheSize;
    std::string L3CacheSize;
	int Index;
};

class FCPUInfoCollector
{
public:
    FCPUInfoCollector();
    inline const std::vector<FCPUInfo>& GetCPUsInformation() const { return CPUsInfo; }
    inline int GetCPUCount() const { return CPUCount; }

private:
	const char* FetchClockSpeed(uint8_t cpuIndex) const;
	const char* FetchTemperature() const;
	const char* DetermineArchitecture(const std::string& dataWidth) const;

private:
	std::vector<FCPUInfo> CPUsInfo;
	int CPUCount;
};