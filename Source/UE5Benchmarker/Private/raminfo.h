#pragma once

#include "systemcommand.h"

struct FRAMInformation
{
	std::string Name = "";
	std::string Manufacturer = "";
	std::string Capacity = "";
	std::string SerialNumber = "";
	std::string FormFactor = "";
	std::string PartNumber = "";
	std::string MemoryType = "";
	std::string ClockSpeed = "";

	uint8_t Index = 0u;
};

class FRAMInformationGatherer
{
public:
	FRAMInformationGatherer();

	inline const std::vector<FRAMInformation>& GetRAMsInformation() const { return RAMsInformation; }
	inline int GetRAMCount() const { return RAMCount; }

private:
	std::string DetermineMemoryType(const std::string& formFactorString) const;
	std::string DetermineFormFactor(const std::string& formFactorString) const;

	std::vector<FRAMInformation> RAMsInformation;
	int RAMCount;

	void FetchNumberOfRams(const std::vector<std::string>& data);

	static const std::string NAME_IDENTIFIER_STRING;
	static const std::string MANUFACTURER_IDENTIFIER_STRING;
	static const std::string CAPACITY_IDENTIFIER_STRING;
	static const std::string SERIAL_NUMBER_IDENTIFIER_STRING;
	static const std::string FORM_FACTOR_IDENTIFIER_STRING;
	static const std::string PART_NUMBER_IDENTIFIER_STRING;
	static const std::string CLOCK_SPEED_IDENTIFIER_STRING;
	static const std::string MEMORY_TYPE_IDENTIFIER_STRING;
	static const std::string BACKUP_CLOCK_SPEED_IDENTIFIER_STRING;
	static const int BYTES_PER_MEGABYTE;
};