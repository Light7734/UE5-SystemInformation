#include "InfoCPU.h"
#include "SystemCommand.h"

#define TEMPERATURE_QUERY_STRING "wmic /namespace:\\\\root\\wmi PATH MSAcpi_ThermalZoneTemperature get CurrentTemperature"
#define CLOCK_SPEED_QUERY_STRING "wmic cpu get /format:list | findstr /R /C:CurrentClockSpeed="

#define	CPU_INFO_QUERY_STRING ""
#define CPU_INSTANCE_QUERY_STRING "AssetTag="
#define CPU_INFO_END_IDENTIFIER_STRING "VoltageCaps="

namespace HardwareInfo {

	std::vector<FCPU::Info> FCPU::FetchInfo()
	{
		// query cpus
		FSystemCommand cpusQuery("wmic path Win32_Processor get /format: list");

		if (cpusQuery.HasFailed())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to query CPUs"));
			return {};
		}

		// fetch cpus info
		std::vector<Info> cpusInfo;
		Info cpuInfo;

		uint32_t index = 1u;
		for (auto it : cpusQuery.GetResult())
		{
			TryFetchField(it, "Architecture=", cpuInfo.Architecture);
			TryFetchField(it, "Availability=", cpuInfo.Availability);
			TryFetchField(it, "Caption=", cpuInfo.Caption);
			TryFetchField(it, "Characteristics=", cpuInfo.Characteristics);
			TryFetchField(it, "CpuStatus=", cpuInfo.CpuStatus);
			TryFetchField(it, "CurrentClockSpeed=", cpuInfo.CurrentClockSpeed);
			TryFetchField(it, "CurrentVoltage=", cpuInfo.CurrentVoltage);
			TryFetchField(it, "Description=", cpuInfo.Description);
			TryFetchField(it, "DeviceID=", cpuInfo.DeviceID);
			TryFetchField(it, "ExtClock=", cpuInfo.ExtClock);
			TryFetchField(it, "Family=", cpuInfo.Family);
			TryFetchField(it, "L2CacheSize=", cpuInfo.L2CacheSize);
			TryFetchField(it, "L3CacheSize=", cpuInfo.L3CacheSize);
			TryFetchField(it, "LoadPercentage=", cpuInfo.LoadPercentage);
			TryFetchField(it, "Manufacturer=", cpuInfo.Manufacturer);
			TryFetchField(it, "MaxClockSpeed=", cpuInfo.MaxClockSpeed);
			TryFetchField(it, "Name=", cpuInfo.Name);
			TryFetchField(it, "NumberOfCores=", cpuInfo.NumberOfCores);
			TryFetchField(it, "NumberOfEnabledCore=", cpuInfo.NumberOfEnabledCore);
			TryFetchField(it, "NumberOfLogicalProcessors=", cpuInfo.NumberOfLogicalProcessors);
			TryFetchField(it, "SecondLevelAddressTranslationExtensions=", cpuInfo.SecondLevelAddressTranslationExtensions);
			TryFetchField(it, "SocketDesignation=", cpuInfo.SocketDesignation);
			TryFetchField(it, "Status=", cpuInfo.Status);

			TryFetchField(it, "ThreadCount=", cpuInfo.ThreadCount);

			if (it.find("Version=") == 0u)
			{
				cpuInfo.Index = index++;

				// store current cpu info then reset it
				cpusInfo.push_back(cpuInfo);
				cpuInfo = Info();
			}
		}

		return cpusInfo;
	}

	void FCPU::TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue)
	{
		if (outValue != INFO_STR_UNKNOWN)
			return;

		outValue = iter.find(fieldName) != std::string::npos ? iter.substr(iter.find(fieldName) + std::strlen(fieldName)) : INFO_STR_UNKNOWN;

		if (outValue == "")
			outValue = INFO_STR_UNKNOWN;
	}


	const char* FCPU::FetchClockSpeed(uint8_t cpuIndex)
	{
		return "";
		// FSystemCommand clockSpeedQuery{ CLOCK_SPEED_QUERY_STRING };
		// const char* clockSpeed = UNKNOWN_INFO_STR;
		// 
		// if (clockSpeedQuery.HasFailed() || clockSpeedQuery.GetResult().empty())
		// 	return clockSpeed;
		// 
		// int cpuInfoNumber = 0;
		// 
		// std::string speed = clockSpeedQuery.GetResult()[cpuIndex];
		// if ((speed.find(CURRENT_CLOCK_SPEED_IDENTIFIER_STRING) != std::string::npos) && (speed.find(CURRENT_CLOCK_SPEED_IDENTIFIER_STRING) == 0))
		// 	clockSpeed = (speed.substr(speed.find(CURRENT_CLOCK_SPEED_IDENTIFIER_STRING) + std::strlen(CURRENT_CLOCK_SPEED_IDENTIFIER_STRING)) + "MHz").c_str();
		// 
		// // #todo: validate
		// if ((!strcmp(clockSpeed, "MHz")) || !strcmp(clockSpeed, ""))
		// 	clockSpeed = "Unknown";
		// 
		// return clockSpeed;
	}

	const char* FCPU::FetchTemperature()
	{
		return "";
		// // #todo: I have no idea what's this
		// // 
		// // NOTE: THIS IS NOT SUPPORTED BY ALL COMPUTERS !!!
		// const char* temperature = INFO_STR_UNKNOWN;
		// FSystemCommand temperatureQuery{ TEMPERATURE_QUERY_STRING };
		// 
		// if (temperatureQuery.HasFailed())
		// 	return temperature;
		// 
		// for (const auto& iter : temperatureQuery)
		// {
		// 	if (iter.find(TEMPERATURE_ERROR_IDENTIFIER_STRING))
		// 		continue;
		// 
		// 	std::string rawTemp = *(temperatureQuery.begin() + 1);
		// 	try {
		// 		temperature = (std::to_string(std::stoi(rawTemp) - 273) + "C").c_str();
		// 	}
		// 	catch (std::exception& e) {
		// 		(void)e;
		// 		return temperature;
		// 	}
		// }
		// 
		// return temperature;
	}

	const char* FCPU::DetermineArchitecture(const std::string& dataWidth)
	{
		return "";
		// try {
		// 	int dataWidthInt = std::stoi(dataWidth);
		// 	switch (dataWidthInt) {
		// 	case 32: return "x86";
		// 	case 64: return "x86_64";
		// 	default: return "Unknown";
		// 	}
		// }
		// catch (std::exception& e) {
		// 	(void)e;
		// 	return "Unknown";
		// }
	}

}