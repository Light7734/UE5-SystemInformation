#pragma once

#include "InfoBase.h"

#include <vector>

class FMotherboardInfo
{
public:
	std::string Name = UNDETECTED_INFO_STR;
	std::string Manufacturer = UNDETECTED_INFO_STR;
	std::string Chipset = UNDETECTED_INFO_STR;
	std::string SerialNumber = UNDETECTED_INFO_STR;
	std::string Version = UNDETECTED_INFO_STR;

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

