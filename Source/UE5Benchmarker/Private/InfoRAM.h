#pragma once

#include "InfoBase.h"

#include <vector>

struct FRAMInformation
{
	std::string Name = UNDETECTED_INFO_STR;
	std::string Manufacturer = UNDETECTED_INFO_STR;
	std::string Capacity = UNDETECTED_INFO_STR;
	std::string SerialNumber = UNDETECTED_INFO_STR;
	std::string FormFactor = UNDETECTED_INFO_STR;
	std::string PartNumber = UNDETECTED_INFO_STR;
	std::string MemoryType = UNDETECTED_INFO_STR;
	std::string ClockSpeed = UNDETECTED_INFO_STR;

	uint8_t Index = 0u;
};

class FRAMInformationCollector
{
public:
	FRAMInformationCollector();

	inline const std::vector<FRAMInformation>& GetRAMsInformation() const { return RAMsInformation; }
	inline int GetRAMCount() const { return RAMCount; }

private:
	std::string DetermineMemoryType(const std::string& formFactorString) const;
	std::string DetermineFormFactor(const std::string& formFactorString) const;

	std::vector<FRAMInformation> RAMsInformation;
	uint8_t RAMCount;

	void FetchNumberOfRams(const std::vector<std::string>& data);
};