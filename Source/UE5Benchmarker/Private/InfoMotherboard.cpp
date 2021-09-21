#include "InfoMotherboard.h"
#include "SystemCommand.h"

#define CHIPSET_QUERY_STRING "wmic path Win32_PnPEntity get /format:list | findstr /R /C:\"Chipset\""
#define NAME_IDENTIFIER_STRING "Product="
#define MANUFACTURER_IDENTIFIER_STRING "Manufacturer="
#define CHIPSET_IDENTIFIER_STRING "Description="
#define CHIPSET_END_IDENTIFIER_STRING "Chipset"
#define SERIAL_NUMBER_IDENTIFIER_STRING "SerialNumber="
#define VERSION_IDENTIFIER_STRING "Version="

#define MOTHERBOARD_INFO_QUERY_STRING "wmic baseboard get /format: list"
#define MOTHERBOARD_INSTANCE_QUERY_STRING "RequiresDaughterBoard="
#define MOTHERBOARD_INFO_END_IDENTIFIER_STRING "Width="

FMotherboardInfoCollector::FMotherboardInfoCollector()
	: MotherboardCount(0u)

{
	FSystemCommand motherboardsQuery(MOTHERBOARD_INFO_QUERY_STRING);
	if (motherboardsQuery.HasFailed())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to quety motherboard(s)"));
		return;
	}

	// fetch motherboard count
	for (const auto& iter : motherboardsQuery.GetResult())
		if (iter.find(MOTHERBOARD_INSTANCE_QUERY_STRING) != std::string::npos)
			MotherboardCount++;

	for (uint8_t i = 0u; i < MotherboardCount; i++) 
	{
		FMotherboardInfo motherboardInformation;
		motherboardInformation.Index = i + 1;

		for (auto iter = motherboardsQuery.GetResult().begin(); iter->find(MOTHERBOARD_INFO_END_IDENTIFIER_STRING) == std::string::npos; iter++)
		{
			// name
			if (FIND_IN_ITER(NAME_IDENTIFIER_STRING))
				motherboardInformation.Name = iter->substr(iter->find(NAME_IDENTIFIER_STRING) + std::strlen(NAME_IDENTIFIER_STRING));

			// manufacturer
			if (FIND_IN_ITER(MANUFACTURER_IDENTIFIER_STRING))
				motherboardInformation.Manufacturer = iter->substr(iter->find(MANUFACTURER_IDENTIFIER_STRING) + std::strlen(MANUFACTURER_IDENTIFIER_STRING));

			// serial number
			if (FIND_IN_ITER(SERIAL_NUMBER_IDENTIFIER_STRING))
				motherboardInformation.SerialNumber = iter->substr(iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) + std::strlen(SERIAL_NUMBER_IDENTIFIER_STRING));

			// motherboard version
			if (FIND_IN_ITER(VERSION_IDENTIFIER_STRING))
				motherboardInformation.Version = iter->substr(iter->find(VERSION_IDENTIFIER_STRING) + std::strlen(VERSION_IDENTIFIER_STRING));
		}

		FSystemCommand chipsetQuery(CHIPSET_QUERY_STRING);
		if (chipsetQuery.HasFailed())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to query chipset for motherboard %i"), i + 1);
			return;
		}

		for (auto iter = chipsetQuery.GetResult().begin(); iter != chipsetQuery.GetResult().end(); iter++)
		{
			if (iter->find(CHIPSET_IDENTIFIER_STRING) != std::string::npos)
			{
				size_t foundPosition = iter->find(CHIPSET_IDENTIFIER_STRING);
				size_t endPosition = iter->find(CHIPSET_END_IDENTIFIER_STRING);
				motherboardInformation.Chipset = iter->substr(foundPosition + std::strlen(CHIPSET_IDENTIFIER_STRING), endPosition - std::strlen(CHIPSET_END_IDENTIFIER_STRING));
			}
		}

		MotherboardsInformation.push_back(motherboardInformation);
	}
}