#include "InfoOS.h"
#include "SystemCommand.h"

#define KILOBYTES_PER_MEGABYTE 1000

namespace HardwareInfo {

	std::vector<FOperatingSystem::Info> FOperatingSystem::FetchInfo()
	{
		// query operating-systems
		FSystemCommand operatingSystemsQuery("wmic path Win32_OperatingSystem get /format:list");

		if (operatingSystemsQuery.HasFailed())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to query operating system"));
			return {};
		}

		// fetch operating-systems info
		std::vector<Info> operatingSystemsInfo;
		Info operatingSystemInfo;

		uint32_t index = 1u;
		for (auto it : operatingSystemsQuery.GetResult())
		{
			TryFetchField(it, "BuildNumber=", operatingSystemInfo.BuildNumber);
			TryFetchField(it, "BuildType=", operatingSystemInfo.BuildType);
			TryFetchField(it, "Caption=", operatingSystemInfo.Caption);
			TryFetchField(it, "DataExecutionPrevention_32BitApplications=", operatingSystemInfo.DataExecutionPrevention_32BitApplications);
			TryFetchField(it, "DataExecutionPrevention_Available=", operatingSystemInfo.DataExecutionPrevention_Available);
			TryFetchField(it, "DataExecutionPrevention_Drivers=", operatingSystemInfo.DataExecutionPrevention_Drivers);
			TryFetchField(it, "DataExecutionPrevention_SupportPolicy=", operatingSystemInfo.DataExecutionPrevention_SupportPolicy);
			TryFetchField(it, "Distributed=", operatingSystemInfo.Distributed);
			TryFetchField(it, "ForegroundApplicationBoost=", operatingSystemInfo.ForegroundApplicationBoost);
			TryFetchField(it, "FreePhysicalMemory=", operatingSystemInfo.FreePhysicalMemory);
			TryFetchField(it, "FreeSpaceInPagingFiles=", operatingSystemInfo.FreeSpaceInPagingFiles);
			TryFetchField(it, "FreeVirtualMemory=", operatingSystemInfo.FreeVirtualMemory);
			TryFetchField(it, "Manufacturer=", operatingSystemInfo.Manufacturer);
			TryFetchField(it, "MaxNumberOfProcesses=", operatingSystemInfo.MaxNumberOfProcesses);
			TryFetchField(it, "MaxProcessMemorySize=", operatingSystemInfo.MaxProcessMemorySize);
			TryFetchField(it, "OSArchitecture=", operatingSystemInfo.OSArchitecture);
			TryFetchField(it, "PortableOperatingSystem=", operatingSystemInfo.PortableOperatingSystem);
			TryFetchField(it, "Primary=", operatingSystemInfo.Primary);
			TryFetchField(it, "ProductType=", operatingSystemInfo.ProductType);
			TryFetchField(it, "SizeStoredInPagingFiles=", operatingSystemInfo.SizeStoredInPagingFiles);
			TryFetchField(it, "Status=", operatingSystemInfo.Status);
			TryFetchField(it, "TotalVirtualMemorySize=", operatingSystemInfo.TotalVirtualMemorySize);
			TryFetchField(it, "TotalVisibleMemorySize=", operatingSystemInfo.TotalVirtualMemorySize);
			TryFetchField(it, "Version=", operatingSystemInfo.Version);

			if (it.find("Version=") == 0u)
			{
				operatingSystemInfo.Index = index++;
				
				// translate enum types
				operatingSystemInfo.DataExecutionPrevention_SupportPolicy = TranslateDataExecutionPrevention_SupportPolicy(operatingSystemInfo.DataExecutionPrevention_SupportPolicy);
				operatingSystemInfo.ForegroundApplicationBoost = TranslateForegroundApplicationBoost(operatingSystemInfo.ForegroundApplicationBoost);
				operatingSystemInfo.ProductType = TranslateProductType(operatingSystemInfo.ProductType);

				// convert values
				operatingSystemInfo.FreePhysicalMemory = HardwareInfo::ConvertBytesToGigabytes(operatingSystemInfo.FreePhysicalMemory);
				operatingSystemInfo.FreeSpaceInPagingFiles = HardwareInfo::ConvertBytesToGigabytes(operatingSystemInfo.FreeSpaceInPagingFiles);
				operatingSystemInfo.FreeVirtualMemory = HardwareInfo::ConvertBytesToGigabytes(operatingSystemInfo.FreeVirtualMemory);
				operatingSystemInfo.MaxProcessMemorySize = HardwareInfo::ConvertBytesToGigabytes(operatingSystemInfo.MaxProcessMemorySize);
				operatingSystemInfo.TotalVirtualMemorySize = HardwareInfo::ConvertBytesToGigabytes(operatingSystemInfo.TotalVirtualMemorySize);
				operatingSystemInfo.TotalVisibleMemorySize = HardwareInfo::ConvertBytesToGigabytes(operatingSystemInfo.TotalVisibleMemorySize);


				// information that could be extracted from the 'wmic' command ends here
                // insert further instructions here
                // ...


				// store current operating-system info then reset it
				operatingSystemsInfo.push_back(operatingSystemInfo);
				operatingSystemInfo = Info();
			}
		}

		return operatingSystemsInfo;
	}

	void FOperatingSystem::TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue)
	{
		if (outValue != INFO_STR_UNKNOWN)
			return;

		outValue = iter.find(fieldName) == 0u ? iter.substr(std::strlen(fieldName)) : INFO_STR_UNKNOWN;

		if (outValue == "")
			outValue = INFO_STR_UNKNOWN;
	}

	const char* FOperatingSystem::TranslateDataExecutionPrevention_SupportPolicy(const std::string& dataExecutionPrevention_SupportPolicy)
	{
		try
		{
			switch (std::stoi(dataExecutionPrevention_SupportPolicy))
			{
			case 0: return "Always Off";
			case 1: return "Always On";
			case 2: return "Opt In";
			case 3: return "Opt Out";
			default: return INFO_STR_UNKNOWN;
			}
		}
		catch (std::exception e)
		{
			(void)e;
			UE_LOG(LogTemp, Error, TEXT("Failed to translate operating system DataExecutionPrevention_SupportPolicy: %s"), *FString(dataExecutionPrevention_SupportPolicy.c_str()));
			return "";
		}
	}

	const char* FOperatingSystem::TranslateForegroundApplicationBoost(const std::string& foregroundApplicationBoost)
	{
		try
		{
			switch (std::stoi(foregroundApplicationBoost))
			{
			case 0: return "None";
			case 1: return "Minimum";
			case 2: return "Maximum";
			default: return INFO_STR_UNKNOWN;
			}
		}
		catch (std::exception e)
		{
			(void)e;
			UE_LOG(LogTemp, Error, TEXT("Failed to translate operating system foreground application boost: %s"), *FString(foregroundApplicationBoost.c_str()));
			return "";
		}
	}

	const char* FOperatingSystem::TranslateProductType(const std::string& productType)
	{
		try
		{
			switch (std::stoi(productType))
			{
			case 1: return "Work Station";
			case 2: return "Domain Controller";
			case 3: return "Server";
			default: return INFO_STR_UNKNOWN;
			}
		}
		catch (std::exception e)
		{
			(void)e;
			UE_LOG(LogTemp, Error, TEXT("Failed to translate operating system product type: %s"), *FString(productType.c_str()));
			return "";
		}
	}

}