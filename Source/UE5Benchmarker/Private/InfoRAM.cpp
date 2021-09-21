#include "InfoRAM.h"
#include "systemcommand.h"

#define NAME_IDENTIFIER_STRING "DeviceLocator="
#define MANUFACTURER_IDENTIFIER_STRING "Manufacturer="
#define CAPACITY_IDENTIFIER_STRING "Capacity="
#define SERIAL_NUMBER_IDENTIFIER_STRING "SerialNumber="
#define FORM_FACTOR_IDENTIFIER_STRING "FormFactor="
#define PART_NUMBER_IDENTIFIER_STRING "PartNumber="
#define MEMORY_TYPE_IDENTIFIER_STRING "MemoryType="
#define CLOCK_SPEED_IDENTIFIER_STRING "ConfiguredClockSpeed="
#define BACKUP_CLOCK_SPEED_IDENTIFIER_STRING "Speed="
#define BYTES_PER_MEGABYTE 1000000 // #todo: check this
#define RAM_INFO_QUERY_STRING "wmic memorychip get /format: list"
#define RAM_INSTANCE_IDENTIFIER_STRING "ConfiguredClockSpeed="
#define RAM_INFO_END_IDENTIFIER_STRING "Version="

FRAMInformationCollector::FRAMInformationCollector()
	: RAMCount(0u)
{
	FSystemCommand RAMsQuery(RAM_INFO_QUERY_STRING);
	if (RAMsQuery.HasFailed())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to query RAMs"));
		return;
	}

	// fetch ram-count
	for (auto iter = RAMsQuery.GetResult().begin(); iter != RAMsQuery.GetResult().end(); iter++)
		if (iter->find(RAM_INSTANCE_IDENTIFIER_STRING) != std::string::npos)
			RAMCount++;

	for (uint8_t i = 0u; i < RAMCount; i++)
	{
		FRAMInformation RAMInfo;
		RAMInfo.Index = i + 1;

		std::string backupClockSpeed = "";

		for (auto iter = RAMsQuery.GetResult().begin(); iter->find(RAM_INFO_END_IDENTIFIER_STRING) == std::string::npos; iter++)
		{
			// name
			if (FIND_IN_ITER(NAME_IDENTIFIER_STRING))
				RAMInfo.Name = iter->substr(iter->find(NAME_IDENTIFIER_STRING) + std::strlen(NAME_IDENTIFIER_STRING));

			// manufacturer
			if (FIND_IN_ITER(MANUFACTURER_IDENTIFIER_STRING))
				RAMInfo.Manufacturer = iter->substr(iter->find(MANUFACTURER_IDENTIFIER_STRING) + std::strlen(MANUFACTURER_IDENTIFIER_STRING));

			// capacity
			if (FIND_IN_ITER(CAPACITY_IDENTIFIER_STRING))
			{
				size_t foundPosition = iter->find(CAPACITY_IDENTIFIER_STRING);
				std::string capacityString = iter->substr(foundPosition + std::strlen(CAPACITY_IDENTIFIER_STRING));
				if (capacityString == "")
				{
					RAMInfo.Capacity = "";
					continue;
				}
				else
				{
					uint64_t capacity = 0u;
					try
					{
						capacity = std::stoll(capacityString);
						RAMInfo.Capacity = std::to_string(capacity / BYTES_PER_MEGABYTE) + "MB (" + std::to_string(capacity) + " Bytes)";
					}
					catch (std::exception& e)
					{
						(void)e;
						RAMInfo.Capacity = capacityString + " Bytes";
					}
				}
			}

			// serial number
			if (FIND_IN_ITER(SERIAL_NUMBER_IDENTIFIER_STRING))
				RAMInfo.SerialNumber = iter->substr(iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) + std::strlen(SERIAL_NUMBER_IDENTIFIER_STRING));

			// form factor (SODIMM, DIMM, etc)
			if (FIND_IN_ITER(FORM_FACTOR_IDENTIFIER_STRING))
			{
				std::string formFactorString = iter->substr(iter->find(FORM_FACTOR_IDENTIFIER_STRING) + std::strlen(FORM_FACTOR_IDENTIFIER_STRING));
				RAMInfo.FormFactor = DetermineFormFactor(formFactorString); // #todo:
			}

			// part number
			if (FIND_IN_ITER(PART_NUMBER_IDENTIFIER_STRING))
				RAMInfo.PartNumber = iter->substr(iter->find(PART_NUMBER_IDENTIFIER_STRING) + std::strlen(PART_NUMBER_IDENTIFIER_STRING));

			// memory type (DRAM, SDRAM, etc)
			if (FIND_IN_ITER(MEMORY_TYPE_IDENTIFIER_STRING))
			{
				std::string memoryTypeString = iter->substr(iter->find(MEMORY_TYPE_IDENTIFIER_STRING) + std::strlen(MEMORY_TYPE_IDENTIFIER_STRING));
				RAMInfo.MemoryType = DetermineMemoryType(memoryTypeString);
			}

			// clock speed
			if (FIND_IN_ITER(CLOCK_SPEED_IDENTIFIER_STRING))
			{
				RAMInfo.ClockSpeed = iter->substr(iter->find(CLOCK_SPEED_IDENTIFIER_STRING) + std::strlen(CLOCK_SPEED_IDENTIFIER_STRING)) + "MHz";

				if (RAMInfo.ClockSpeed == "MHz")
					RAMInfo.ClockSpeed = UNDETECTED_INFO_STR;
			}

			// backup clock speed
			if (FIND_IN_ITER(BACKUP_CLOCK_SPEED_IDENTIFIER_STRING))
			{
				backupClockSpeed = iter->substr(iter->find(BACKUP_CLOCK_SPEED_IDENTIFIER_STRING) + std::strlen(BACKUP_CLOCK_SPEED_IDENTIFIER_STRING)) + "MHz";

				if (backupClockSpeed == "MHz")
					backupClockSpeed = UNDETECTED_INFO_STR;
			}
		}

		if (RAMInfo.ClockSpeed == UNDETECTED_INFO_STR)
			RAMInfo.ClockSpeed = backupClockSpeed;

		RAMsInformation.push_back(RAMInfo);
	}
}
std::string FRAMInformationCollector::DetermineMemoryType(const std::string& memoryTypeString) const
{
	int memoryType = 0;
	try {
		memoryType = std::stoi(memoryTypeString);
	}
	catch (std::exception& e) {
		(void)e;
		memoryType = 0;
	}

	// https://msdn.microsoft.com/en-us/library/aa394347(v=vs.85).aspx
	switch (memoryType)
	{
		case 0: return UNDETECTED_INFO_STR;
		case 1: return "Other";
		case 2: return "DRAM";
		case 3: return "Synchronous DRAM";
		case 4: return "Cache DRAM";
		case 5: return "EDO";
		case 6: return "EDRAM";
		case 7: return "VRAM";
		case 8: return "SRAM";
		case 9: return "RAM";
		case 10: return "ROM";
		case 11: return "Flash";
		case 12: return "EEPROM";
		case 13: return "FEPROM";
		case 14: return "EPROM";
		case 15: return "CDRAM";
		case 16: return "3DRAM";
		case 17: return "SDRAM";
		case 18: return "SGRAM";
		case 19: return "RDRAM";
		case 20: return "DDR1";
		case 21: return "DDR2";
		case 22: return "DDR2 - FBDIMM";
		case 23: return "DDR2 - FBDIMM";
		case 24: return "DDR3";
		case 25: return "FBD2";
		default: return UNKNOWN_INFO_STR;
	}
}

std::string FRAMInformationCollector::DetermineFormFactor(const std::string &formFactorString) const
{
	int formFactor = 0;
	try 
	{
		formFactor = std::stoi(formFactorString);
	} 
	catch (std::exception &e)
	{
		(void)e;
		formFactor = 0;
	}

    // https://msdn.microsoft.com/en-us/library/aa394347(v=vs.85).aspx
	switch (formFactor) {
		case 0: return UNDETECTED_INFO_STR;
		case 1: return "Other";
		case 2: return "SIP";
		case 3: return "DIP";
		case 4: return "ZIP";
		case 5: return "SOJ";
		case 6: return "Proprietary";
		case 7: return "SIMM";
		case 8: return "DIMM";
		case 9: return "TSOP";
		case 10: return "PGA";
		case 11: return "RIMM";
		case 12: return "SODIMM";
		case 13: return "SRIMM";
		case 14: return "SMD";
		case 15: return "SSMP";
		case 16: return "QFD";
		case 17: return "TQFP";
		case 18: return "SOIC";
		case 19: return "LCC";
		case 20: return "PLCC";
		case 21: return "BGA";
		case 22: return "FPBGA";
		case 23: return "LGA";
		default: return UNKNOWN_INFO_STR;
	}
}

void FRAMInformationCollector::FetchNumberOfRams(const std::vector<std::string>& data)
{

}