#pragma once

#include "InfoBase.h"

#include <vector>

struct FGPUInfo
{
    std::string Name = UNDETECTED_INFO_STR;
    std::string Manufacturer = UNDETECTED_INFO_STR;
    std::string Caption = UNDETECTED_INFO_STR;
    std::string AdapterRAM = UNDETECTED_INFO_STR;
    std::string RefreshRate = UNDETECTED_INFO_STR;
    std::string DriverVersion = UNDETECTED_INFO_STR;
    std::string VideoArchitecture = UNDETECTED_INFO_STR;
    std::string VideoMemoryType = UNDETECTED_INFO_STR;
    std::string VideoModeDescription = UNDETECTED_INFO_STR;
    std::string VideoProcessor = UNDETECTED_INFO_STR;
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