#include "InfoCPU.h"
#include "SystemCommand.h"

#define TEMPERATURE_QUERY_STRING "wmic /namespace:\\\\root\\wmi PATH MSAcpi_ThermalZoneTemperature get CurrentTemperature"
#define CLOCK_SPEED_QUERY_STRING "wmic cpu get /format:list | findstr /R /C:CurrentClockSpeed="

#define TEMPERATURE_ERROR_IDENTIFIER_STRING "ERROR:"
#define CURRENT_CLOCK_SPEED_IDENTIFIER_STRING "CurrentClockSpeed="
#define NAME_IDENTIFIER_STRING "Name="
#define NUMBER_OF_CORES_IDENTIFIER_STRING "NumberOfCores="
#define MANUFACTURER_IDENTIFIER_STRING "Manufacturer="
#define ARCHITECTURE_IDENTIFIER_STRING "DataWidth="
#define L2_CACHE_SIZE_IDENTIFIER_STRING "L2CacheSize="
#define L3_CACHE_SIZE_IDENTIFIER_STRING "L3CacheSize="

#define	CPU_INFO_QUERY_STRING "wmic cpu get /format: list"
#define CPU_INSTANCE_QUERY_STRING "AssetTag="
#define CPU_INFO_END_IDENTIFIER_STRING "VoltageCaps="

FCPUInfoCollector::FCPUInfoCollector()
	: CPUCount(0u)
{
	FSystemCommand CPUsQuery{ CPU_INFO_QUERY_STRING };

	if (CPUsQuery.HasFailed())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to query CPUs"));
		return;
	}

	// Fetch cpu count
	for (const auto& iter : CPUsQuery)
		if (iter.find(CPU_INSTANCE_QUERY_STRING) != std::string::npos)
			CPUCount++;

	for (uint8_t i = 0; i < CPUCount; i++)
	{
		FCPUInfo CPUInfo;
		CPUInfo.Index = i + 1;

		for (auto iter = CPUsQuery.GetResult().begin(); iter->find(CPU_INFO_END_IDENTIFIER_STRING) == std::string::npos; iter++)
		{
			//Name
			if ((iter->find(NAME_IDENTIFIER_STRING) != std::string::npos) && (iter->find(NAME_IDENTIFIER_STRING) == 0))
				CPUInfo.Name = iter->substr(iter->find(NAME_IDENTIFIER_STRING) + std::strlen(NAME_IDENTIFIER_STRING));

			//Manufacturer
			if ((iter->find(MANUFACTURER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(MANUFACTURER_IDENTIFIER_STRING) == 0))
				CPUInfo.Manufacturer = iter->substr(iter->find(MANUFACTURER_IDENTIFIER_STRING) + std::strlen(MANUFACTURER_IDENTIFIER_STRING));

			//Number Of Cores
			if ((iter->find(NUMBER_OF_CORES_IDENTIFIER_STRING) != std::string::npos) && (iter->find(NUMBER_OF_CORES_IDENTIFIER_STRING) == 0))
				CPUInfo.CoreCount = iter->substr(iter->find(NUMBER_OF_CORES_IDENTIFIER_STRING) + std::strlen(NUMBER_OF_CORES_IDENTIFIER_STRING));

			//Architecture
			if ((iter->find(ARCHITECTURE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(ARCHITECTURE_IDENTIFIER_STRING) == 0))
				CPUInfo.Architecture = DetermineArchitecture(iter->substr(iter->find(ARCHITECTURE_IDENTIFIER_STRING) + std::strlen(ARCHITECTURE_IDENTIFIER_STRING)));

			//L2 Cache Size
			if ((iter->find(L2_CACHE_SIZE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(L2_CACHE_SIZE_IDENTIFIER_STRING) == 0))
			{
				CPUInfo.L2CacheSize = iter->substr(iter->find(L2_CACHE_SIZE_IDENTIFIER_STRING) + std::strlen(L2_CACHE_SIZE_IDENTIFIER_STRING)) + "KB";

				if (CPUInfo.L2CacheSize == "KB")
					CPUInfo.L2CacheSize = "";
			}

			//L3 Cache Size
			if ((iter->find(L3_CACHE_SIZE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(L3_CACHE_SIZE_IDENTIFIER_STRING) == 0))
			{
				CPUInfo.L3CacheSize = iter->substr(iter->find(L3_CACHE_SIZE_IDENTIFIER_STRING) + std::strlen(L3_CACHE_SIZE_IDENTIFIER_STRING)) + "KB";

				if (CPUInfo.L3CacheSize == "KB")
					CPUInfo.L3CacheSize = "";
			}
		}
		CPUsInfo.push_back(CPUInfo);
	}
}

const char* FCPUInfoCollector::FetchClockSpeed(uint8_t cpuIndex) const
{
	FSystemCommand clockSpeedQuery{ CLOCK_SPEED_QUERY_STRING };
	const char* clockSpeed = UNKNOWN_INFO_STR;

	if (clockSpeedQuery.HasFailed() || clockSpeedQuery.GetResult().empty())
		return clockSpeed;

	int cpuInfoNumber = 0;

	std::string speed = clockSpeedQuery.GetResult()[cpuIndex];
	if ((speed.find(CURRENT_CLOCK_SPEED_IDENTIFIER_STRING) != std::string::npos) && (speed.find(CURRENT_CLOCK_SPEED_IDENTIFIER_STRING) == 0))
		clockSpeed = (speed.substr(speed.find(CURRENT_CLOCK_SPEED_IDENTIFIER_STRING) + std::strlen(CURRENT_CLOCK_SPEED_IDENTIFIER_STRING)) + "MHz").c_str();

	// #todo: validate
	if ((!strcmp(clockSpeed,"MHz")) || !strcmp(clockSpeed, ""))
		clockSpeed = "Unknown";

	return clockSpeed;
}

const char* FCPUInfoCollector::FetchTemperature() const
{
	// #todo: I have no idea what's this
	// 
	// NOTE: THIS IS NOT SUPPORTED BY ALL COMPUTERS !!!
	const char* temperature = INFO_STR_UNKNOWN;
	FSystemCommand temperatureQuery{ TEMPERATURE_QUERY_STRING };

	if (temperatureQuery.HasFailed())
		return temperature;

	for (const auto& iter : temperatureQuery)
	{
		if (iter.find(TEMPERATURE_ERROR_IDENTIFIER_STRING))
			continue;
		
		std::string rawTemp = *(temperatureQuery.begin() + 1);
		try {
			temperature = (std::to_string(std::stoi(rawTemp) - 273) + "C").c_str();
		} catch (std::exception &e) {
			(void)e;
			return temperature;
		}
	}

	return temperature;
}

const char* FCPUInfoCollector::DetermineArchitecture(const std::string& dataWidth) const
{
	try {
		int dataWidthInt = std::stoi(dataWidth);
		switch (dataWidthInt) {
			case 32: return "x86";
			case 64: return "x86_64";
			default: return "Unknown";
		}
	} catch (std::exception &e) {
		(void)e;
		return "Unknown";
	}
}