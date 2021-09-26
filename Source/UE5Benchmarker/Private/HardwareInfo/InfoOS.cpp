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
			TryFetchField(it, "OperatingSystemSKU=", operatingSystemInfo.OperatingSystemSKU);
			TryFetchField(it, "OSArchitecture=", operatingSystemInfo.OSArchitecture);
			TryFetchField(it, "OSProductSuite=", operatingSystemInfo.OSProductSuite);
			TryFetchField(it, "OSType=", operatingSystemInfo.OSType);
			TryFetchField(it, "PortableOperatingSystem=", operatingSystemInfo.PortableOperatingSystem);
			TryFetchField(it, "Primary=", operatingSystemInfo.Primary);
			TryFetchField(it, "ProductType=", operatingSystemInfo.ProductType);
			TryFetchField(it, "SizeStoredInPagingFiles=", operatingSystemInfo.SizeStoredInPagingFiles);
			TryFetchField(it, "Status=", operatingSystemInfo.Status);
			TryFetchField(it, "SuiteMask=", operatingSystemInfo.SuiteMask);
			TryFetchField(it, "TotalVirtualMemorySize=", operatingSystemInfo.TotalVirtualMemorySize);
			TryFetchField(it, "TotalVisibleMemorySize=", operatingSystemInfo.TotalVirtualMemorySize);
			TryFetchField(it, "Version=", operatingSystemInfo.Version);

			if (it.find("Version=") == 0u)
			{
				operatingSystemInfo.Index = index++;
				
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

		outValue = iter.find(fieldName) != std::string::npos ? iter.substr(std::strlen(fieldName)) : INFO_STR_UNKNOWN;

		if (outValue == "")
			outValue = INFO_STR_UNKNOWN;
	}

}