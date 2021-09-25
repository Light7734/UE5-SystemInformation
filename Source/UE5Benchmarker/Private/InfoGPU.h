#pragma once

#include "InfoBase.h"

#include <vector>

struct FGPUInfo
{
    std::string Name = INFO_STR_UNKNOWN;
    std::string Manufacturer = INFO_STR_UNKNOWN;
    std::string Caption = INFO_STR_UNKNOWN;
    std::string AdapterRAM = INFO_STR_UNKNOWN;
    std::string RefreshRate = INFO_STR_UNKNOWN;
    std::string DriverVersion = INFO_STR_UNKNOWN;
    std::string VideoArchitecture = INFO_STR_UNKNOWN;
    std::string VideoMemoryType = INFO_STR_UNKNOWN;
    std::string VideoModeDescription = INFO_STR_UNKNOWN;
    std::string VideoProcessor = INFO_STR_UNKNOWN;
	int Index;
};

class FGPUInfoCollector
{
public:
    FGPUInfoCollector();
    inline const std::vector<FGPUInfo>& GetGPUsInformation() const { return GPUsInfo; }
    inline int GetGPUCount() const { return GPUCount; }

private:
	const char* DetermineVideoArchitecture(const std::string videoArchitectureStr) const;
	const char* DetermineVideoMemoryType(const std::string& videoMemoryTypeStr) const;

private:
	std::vector<FGPUInfo> GPUsInfo;
	int GPUCount;
};