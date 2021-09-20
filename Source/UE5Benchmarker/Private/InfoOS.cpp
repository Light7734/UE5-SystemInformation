#include "InfoOS.h"

#define ARCHITECTURE_IDENTIFIER_STRING "OSArchitecture="
#define CAPTION_INDENTIFIER_STRING "Caption="
#define NAME_IDENTIFIER_STRING "Name="
#define MANUFACTURER_IDENTIFIER_STRING "Manufacturer="
#define VERSION_IDENTIFIER_STRING "Version="
#define CURRENT_USER_IDENTIFIER_STRING "RegisteredUser="
#define INSTALL_DATE_IDENTIFIER_STRING "InstallDate="
#define BUILD_NUMBER_IDENTIFIER_STRING "BuildNumber="
#define LAST_BOOT_UP_TIME_IDENTIFIER_STRING "LastBootUpTime="
#define BOOT_DEVICE_IDENTIFIER_STRING "BootDevice="
#define SERIAL_NUMBER_IDENTIFIER_STRING "SerialNumber="
#define TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING "TotalVirtualMemorySize="
#define TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING "TotalVisibleMemorySize="
#define TOTAL_SWAP_SIZE_IDENTIFIER_STRING "TotalSwapSize="

#define FREE_PHYSICAL_MEMORY_IDENTIFIER_STRING = "FreePhysicalMemory=";
#define FREE_PHYSICAL_MEMORY_QUERY_STRING "wmic os get /format:list | findstr /R /C:FreePhysicalMemory="

#define FREE_VIRTUAL_MEMORY_IDENTIFIER_STRING = "FreeVirtualMemory=";
#define FREE_VIRTUAL_MEMORY_QUERY_STRING "wmic os get /format:list | findstr /R /C:FreeVirtualMemory="

#define FREE_SPACE_IN_PAGING_FILES_IDENTIFIER_STRING = "FreeSpaceInPagingFiles=";
#define FREE_SPACE_IN_PAGING_FILES_QUERY_STRING "wmic os get /format:list | findstr /R /C:FreeSpaceInPagingFiles="

#define USED_SPACE_IN_PAGING_FILE_IDENTIFIER_STRING = "SizeStoredInPagingFiles=";
#define USED_SPACE_IN_PAGING_FILE_QUERY_STRING "wmic os get /format:list | findstr /R /C:SizeStoredInPagingFiles="

#define CURRENT_DATE_TIME_IDENTIFIER_STRING = "LocalDateTime=";
#define CURRENT_DATE_TIME_QUERY_STRING "wmic os get /format:list | findstr /R /C:LocalDateTime="

#define KILOBYTES_PER_MEGABYTE 1000

#define OS_INFO_QUERY_STRING "wmic os get /format:list"
#define OS_INSTANCE_QUERY_STRING "PortableOperatingSystem="
#define OS_INFO_END_IDENTIFIER_STRING "WindowsDirectory="

FOSInfoCollector::FOSInfoCollector()
	: OSCount(0u)
{
	FSystemCommand systemCommand(OS_INFO_QUERY_STRING);

	if (systemCommand.HasFailed())
		return; // #todo

	FetchOSCount(systemCommand.GetResult());

	for (uint8_t i = 0; i < OSCount; i++)
	{
		FOSInformation OSInformation;
		OSInformation.Index = i;

		for (auto iter = systemCommand.GetResult().begin(); iter->find(OS_INFO_END_IDENTIFIER_STRING) == std::string::npos; iter++)
		{
			// name
			if (FIND_IN_ITER(NAME_IDENTIFIER_STRING))
				OSInformation.Name = iter->substr(iter->find(NAME_IDENTIFIER_STRING) + std::strlen(NAME_IDENTIFIER_STRING));

			// manufacturer
			if (FIND_IN_ITER(MANUFACTURER_IDENTIFIER_STRING))
				OSInformation.Manufacturer = iter->substr(iter->find(MANUFACTURER_IDENTIFIER_STRING) + std::strlen(MANUFACTURER_IDENTIFIER_STRING));

			// architecture
			if ((iter->find(ARCHITECTURE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(ARCHITECTURE_IDENTIFIER_STRING) == 0))
				OSInformation.Architecture = iter->substr(iter->find(ARCHITECTURE_IDENTIFIER_STRING) + std::strlen(ARCHITECTURE_IDENTIFIER_STRING));

			// caption
			if ((iter->find(CAPTION_INDENTIFIER_STRING) != std::string::npos) && (iter->find(CAPTION_INDENTIFIER_STRING) == 0))
				OSInformation.Caption = iter->substr(iter->find(CAPTION_INDENTIFIER_STRING) + std::strlen(CAPTION_INDENTIFIER_STRING));

			// version
			if ((iter->find(VERSION_IDENTIFIER_STRING) != std::string::npos) && (iter->find(VERSION_IDENTIFIER_STRING) == 0))
				OSInformation.Version = iter->substr(iter->find(VERSION_IDENTIFIER_STRING) + std::strlen(VERSION_IDENTIFIER_STRING));

			// current user
			if ((iter->find(CURRENT_USER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(CURRENT_USER_IDENTIFIER_STRING) == 0))
				OSInformation.CurrentUser = iter->substr(iter->find(CURRENT_USER_IDENTIFIER_STRING) + std::strlen(CURRENT_USER_IDENTIFIER_STRING));

			// install date
			if ((iter->find(INSTALL_DATE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(INSTALL_DATE_IDENTIFIER_STRING) == 0))
				OSInformation.InstallDate = iter->substr(iter->find(INSTALL_DATE_IDENTIFIER_STRING) + std::strlen(INSTALL_DATE_IDENTIFIER_STRING));

			// build number
			if ((iter->find(BUILD_NUMBER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(BUILD_NUMBER_IDENTIFIER_STRING) == 0))
				OSInformation.BuildNumber = iter->substr(iter->find(BUILD_NUMBER_IDENTIFIER_STRING) + std::strlen(BUILD_NUMBER_IDENTIFIER_STRING));

			// last boot-up time
			if ((iter->find(LAST_BOOT_UP_TIME_IDENTIFIER_STRING) != std::string::npos) && (iter->find(LAST_BOOT_UP_TIME_IDENTIFIER_STRING) == 0))
				OSInformation.LastBootUpTime = iter->substr(iter->find(LAST_BOOT_UP_TIME_IDENTIFIER_STRING) + std::strlen(LAST_BOOT_UP_TIME_IDENTIFIER_STRING));

			// boot device
			if ((iter->find(BOOT_DEVICE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(BOOT_DEVICE_IDENTIFIER_STRING) == 0))
				OSInformation.BootDevice = iter->substr(iter->find(BOOT_DEVICE_IDENTIFIER_STRING) + std::strlen(BOOT_DEVICE_IDENTIFIER_STRING));

			// serial number
			if ((iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) == 0))
				OSInformation.SerialNumber = iter->substr(iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) + std::strlen(SERIAL_NUMBER_IDENTIFIER_STRING));

			// total virtual memory
			if ((iter->find(TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING) == 0)) {
				std::string totalVirtualMemoryString = iter->substr(iter->find(TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING) + std::strlen(TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING));
				if (totalVirtualMemoryString == "") {
					OSInformation.TotalVirtualMemory = "";
					continue;
				}
				else {
					long long int totalVirtualMemory{ 0 };
					try {
						totalVirtualMemory = std::stoll(totalVirtualMemoryString);
						OSInformation.TotalVirtualMemory = std::to_string(totalVirtualMemory / KILOBYTES_PER_MEGABYTE) + "MB (" + std::to_string(totalVirtualMemory) + " KB)";
					}
					catch (std::exception& e) {
						(void)e;
						OSInformation.TotalVirtualMemory = totalVirtualMemoryString + " KB";
					}
				}
			}

			// total visible memory
			if ((iter->find(TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING) == 0)) {
				std::string totalVisibleMemoryString = iter->substr(iter->find(TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING) + std::strlen(TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING));
				if (totalVisibleMemoryString == "") {
					OSInformation.TotalVisibleMemory = "";
					continue;
				}
				else {
					long long int totalVisibleMemory{ 0 };
					try {
						totalVisibleMemory = std::stoll(totalVisibleMemoryString);
						OSInformation.TotalVisibleMemory = std::to_string(totalVisibleMemory / KILOBYTES_PER_MEGABYTE) + "MB (" + std::to_string(totalVisibleMemory) + " KB)";
					}
					catch (std::exception& e) {
						(void)e;
						OSInformation.TotalVisibleMemory = totalVisibleMemoryString + " KB";
					}
				}
			}

			// total swap size
			if ((iter->find(TOTAL_SWAP_SIZE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(TOTAL_SWAP_SIZE_IDENTIFIER_STRING) == 0)) {
				size_t foundPosition = iter->find(TOTAL_SWAP_SIZE_IDENTIFIER_STRING);
				std::string totalSwapSizeString = iter->substr(iter->find(TOTAL_SWAP_SIZE_IDENTIFIER_STRING) + std::strlen(TOTAL_SWAP_SIZE_IDENTIFIER_STRING));
				if (totalSwapSizeString == "") {
					OSInformation.TotalSwapSize = "";
					continue;
				}
				else {
					long long int totalSwapSize{ 0 };
					try {
						totalSwapSize = std::stoll(totalSwapSizeString);
						OSInformation.TotalVisibleMemory = std::to_string(totalSwapSize / KILOBYTES_PER_MEGABYTE) + "MB (" + std::to_string(totalSwapSize) + " KB)";
					}
					catch (std::exception& e) {
						(void)e;
						OSInformation.TotalSwapSize = totalSwapSizeString + " KB";
					}
				}
			}
		}

		if ((OSInformation.TotalVirtualMemory == "") || (OSInformation.TotalVirtualMemory == " KB"))
			OSInformation.TotalVirtualMemory = "Unknown";

		if ((OSInformation.TotalVisibleMemory == "") || (OSInformation.TotalVisibleMemory == " KB"))
			OSInformation.TotalVisibleMemory = "Unknown";

		if ((OSInformation.TotalSwapSize == "") || (OSInformation.TotalSwapSize == " KB"))
			OSInformation.TotalSwapSize = "Unknown";

		OSsInformation.push_back(OSInformation);
	}
}

void FOSInfoCollector::FetchOSCount(const std::vector<std::string>& data)
{
	for (auto iter = data.begin(); iter != data.end(); iter++)
		if (iter->find(OS_INSTANCE_QUERY_STRING) != std::string::npos)
			OSCount++;
}