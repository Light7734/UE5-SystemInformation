#pragma once

#include "InfoBase.h"

#include <vector>

class FMotherboardInfo
{
public:
	std::string Name = INFO_STR_UNKNOWN;
	std::string Manufacturer = INFO_STR_UNKNOWN;
	std::string Chipset = INFO_STR_UNKNOWN;
	std::string SerialNumber = INFO_STR_UNKNOWN;
	std::string Version = INFO_STR_UNKNOWN;

	uint8_t Index = 0u;
};

class FMotherboardInfoCollector
{
public:
	FMotherboardInfoCollector();

	inline const std::vector<FMotherboardInfo>& GetMotherboardsInformation() const { return MotherboardsInformation; };
	inline int GetMotherboardCount() const { return MotherboardCount; }

private:
	std::vector<FMotherboardInfo> MotherboardsInformation;
	int MotherboardCount;
};

