#include "raminfo.h"

const std::string FRAMInformationGatherer::NAME_IDENTIFIER_STRING = "DeviceLocator=";
const std::string FRAMInformationGatherer::MANUFACTURER_IDENTIFIER_STRING = "Manufacturer=";
const std::string FRAMInformationGatherer::CAPACITY_IDENTIFIER_STRING = "Capacity=";
const std::string FRAMInformationGatherer::SERIAL_NUMBER_IDENTIFIER_STRING = "SerialNumber=";
const std::string FRAMInformationGatherer::FORM_FACTOR_IDENTIFIER_STRING = "FormFactor=";
const std::string FRAMInformationGatherer::PART_NUMBER_IDENTIFIER_STRING = "PartNumber=";
const std::string FRAMInformationGatherer::MEMORY_TYPE_IDENTIFIER_STRING = "MemoryType=";
const std::string FRAMInformationGatherer::CLOCK_SPEED_IDENTIFIER_STRING = "ConfiguredClockSpeed=";
const std::string FRAMInformationGatherer::BACKUP_CLOCK_SPEED_IDENTIFIER_STRING = "Speed=";
const int FRAMInformationGatherer::BYTES_PER_MEGABYTE = 1000000;

#define RAM_INFO_QUERY_STRING "wmic memorychip get /format: list"
#define RAM_INSTANCE_IDENTIFIER_STRING "ConfiguredClockSpeed="
#define RAM_INFO_END_IDENTIFIER_STRING "Version="

FRAMInformationGatherer::FRAMInformationGatherer()
	: RAMCount(0)
{
	FSystemCommand systemCommand(RAM_INFO_QUERY_STRING);

	if (systemCommand.HasFailed())
		return;

	FetchNumberOfRams(systemCommand.GetResult());

	for (int i = 0; i < this->RAMCount; i++)
	{
		FRAMInformation RAMInfo;
		RAMInfo.Index = i + 1;

		std::string backupClockSpeed{ "" };

		for (auto iter = systemCommand.GetResult().begin(); iter->find(RAM_INFO_END_IDENTIFIER_STRING) == std::string::npos; iter++)
		{
			//if ((*iter != "") && (*iter != "\r"))
			//	RAMInfo.push_back(*iter);

				//Name
			if ((iter->find(NAME_IDENTIFIER_STRING) != std::string::npos) && (iter->find(NAME_IDENTIFIER_STRING) == 0)) {
				size_t foundPosition = iter->find(NAME_IDENTIFIER_STRING);
				RAMInfo.Name = iter->substr(foundPosition + NAME_IDENTIFIER_STRING.length());
			}

			//Manufacturer
			if ((iter->find(MANUFACTURER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(MANUFACTURER_IDENTIFIER_STRING) == 0)) {
				size_t foundPosition = iter->find(MANUFACTURER_IDENTIFIER_STRING);
				RAMInfo.Manufacturer = iter->substr(foundPosition + MANUFACTURER_IDENTIFIER_STRING.length());
			}

			//Capacity
			if ((iter->find(CAPACITY_IDENTIFIER_STRING) != std::string::npos) && (iter->find(CAPACITY_IDENTIFIER_STRING) == 0))
			{
				size_t foundPosition = iter->find(CAPACITY_IDENTIFIER_STRING);
				std::string capacityString = iter->substr(foundPosition + CAPACITY_IDENTIFIER_STRING.length());
				if (capacityString == "")
				{
					RAMInfo.Capacity = "";
					continue;
				}
				else
				{
					long long int capacity{ 0 };
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

			//Serial Number
			if ((iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) == 0))
			{
				size_t foundPosition = iter->find(SERIAL_NUMBER_IDENTIFIER_STRING);
				RAMInfo.SerialNumber = iter->substr(foundPosition + SERIAL_NUMBER_IDENTIFIER_STRING.length());
			}

			//Form Factor (SODIMM, DIMM, etc)
			if ((iter->find(FORM_FACTOR_IDENTIFIER_STRING) != std::string::npos) && (iter->find(FORM_FACTOR_IDENTIFIER_STRING) == 0))
			{
				size_t foundPosition = iter->find(FORM_FACTOR_IDENTIFIER_STRING);
				std::string formFactorString = iter->substr(foundPosition + FORM_FACTOR_IDENTIFIER_STRING.length());
				RAMInfo.FormFactor = DetermineFormFactor(formFactorString);
			}

			//Part Number
			if ((iter->find(PART_NUMBER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(PART_NUMBER_IDENTIFIER_STRING) == 0))
			{
				size_t foundPosition = iter->find(PART_NUMBER_IDENTIFIER_STRING);
				RAMInfo.PartNumber = iter->substr(foundPosition + PART_NUMBER_IDENTIFIER_STRING.length());
			}

			//Memory Type (DRAM, SDRAM, etc)
			if ((iter->find(MEMORY_TYPE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(MEMORY_TYPE_IDENTIFIER_STRING) == 0))
			{
				size_t foundPosition = iter->find(MEMORY_TYPE_IDENTIFIER_STRING);
				std::string memoryTypeString = iter->substr(foundPosition + MEMORY_TYPE_IDENTIFIER_STRING.length());
				RAMInfo.MemoryType = DetermineMemoryType(memoryTypeString);
			}

			//Clock Speed
			if ((iter->find(CLOCK_SPEED_IDENTIFIER_STRING) != std::string::npos) && (iter->find(CLOCK_SPEED_IDENTIFIER_STRING) == 0))
			{
				size_t foundPosition = iter->find(CLOCK_SPEED_IDENTIFIER_STRING);
				RAMInfo.ClockSpeed = iter->substr(foundPosition + CLOCK_SPEED_IDENTIFIER_STRING.length()) + "MHz";
				if (RAMInfo.ClockSpeed == "MHz") {
					RAMInfo.ClockSpeed = "";
				}
			}

			//Backup clock speed
			if ((iter->find(BACKUP_CLOCK_SPEED_IDENTIFIER_STRING) != std::string::npos) && (iter->find(BACKUP_CLOCK_SPEED_IDENTIFIER_STRING) == 0))
			{
				size_t foundPosition = iter->find(BACKUP_CLOCK_SPEED_IDENTIFIER_STRING);
				backupClockSpeed = iter->substr(foundPosition + BACKUP_CLOCK_SPEED_IDENTIFIER_STRING.length()) + "MHz";
				if (backupClockSpeed == "MHz") {
					backupClockSpeed = "";
				}
			}
		}

		//In case any of these values are missing or don't get assigned
		if (RAMInfo.Name == "") {
			RAMInfo.Name = "Unknown";
		}
		if (RAMInfo.Manufacturer == "") {
			RAMInfo.Manufacturer = "Unknown";
		}
		if ((RAMInfo.Capacity == "") || (RAMInfo.Capacity == " Bytes")) {
			RAMInfo.Capacity = "Unknown";
		}
		if (RAMInfo.SerialNumber == "") {
			RAMInfo.SerialNumber = "Unknown";
		}
		if (RAMInfo.PartNumber == "") {
			RAMInfo.PartNumber = "Unknown";
		}
		if ((RAMInfo.ClockSpeed == "") && (backupClockSpeed == "")) {
			RAMInfo.ClockSpeed = "Unknown";
		}
		else if (RAMInfo.ClockSpeed == "") {
			RAMInfo.ClockSpeed = backupClockSpeed;
		}

		RAMsInformation.push_back(RAMInfo);
	}
}
std::string FRAMInformationGatherer::DetermineMemoryType(const std::string& memoryTypeString) const
{
	int memoryType{ 0 };
	try {
		memoryType = std::stoi(memoryTypeString);
	}
	catch (std::exception& e) {
		(void)e;
		memoryType = 0;
	}
	// As per https://msdn.microsoft.com/en-us/library/aa394347(v=vs.85).aspx
	switch (memoryType)
	{
		case 0: return "Unknown";
		case 1: return "Other";
		case 2: return "DRAM";
		case 3: return "Syncronous DRAM";
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
		default: return "Unknown";
	}
}

std::string FRAMInformationGatherer::DetermineFormFactor(const std::string &formFactorString) const
{
	int formFactor{0};
	try {
		formFactor = std::stoi(formFactorString);
	} catch (std::exception &e) {
		(void)e;
		formFactor = 0;
	}
    // As per https://msdn.microsoft.com/en-us/library/aa394347(v=vs.85).aspx
	switch (formFactor) {
		case 0: return "Unknown";
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
		default: return "Unknown";
	}
}

void FRAMInformationGatherer::FetchNumberOfRams(const std::vector<std::string>& data)
{
	for (auto iter = data.begin(); iter != data.end(); iter++)
		if (iter->find(RAM_INSTANCE_IDENTIFIER_STRING) != std::string::npos)
			RAMCount++;
}