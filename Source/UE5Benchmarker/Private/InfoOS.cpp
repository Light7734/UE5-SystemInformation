#include "InfoOS.h"
#include "SystemCommand.h"

#define KILOBYTES_PER_MEGABYTE 1000

namespace HardwareInfo {

	std::vector<FOS::Info> FOS::FetchInfo()
	{
		// query os
		FSystemCommand OSQuery("wmic path Win32_OperatingSystem get /format:list");

		if (OSQuery.HasFailed())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to query operating system"));
			return {};
		}

		// fetch os info
		std::vector<Info> ossInfo;
		Info osInfo;

		uint32_t index = 1u;
		for (auto it : OSQuery.GetResult())
		{
			TryFetchField(it, "BuildNumber=", osInfo.BuildNumber);
			TryFetchField(it, "BuildType=", osInfo.BuildType);
			TryFetchField(it, "Caption=", osInfo.Caption);
			TryFetchField(it, "DataExecutionPrevention_32BitApplications=", osInfo.DataExecutionPrevention_32BitApplications);
			TryFetchField(it, "DataExecutionPrevention_Available=", osInfo.DataExecutionPrevention_Available);
			TryFetchField(it, "DataExecutionPrevention_Drivers=", osInfo.DataExecutionPrevention_Drivers);
			TryFetchField(it, "DataExecutionPrevention_SupportPolicy=", osInfo.DataExecutionPrevention_SupportPolicy);
			TryFetchField(it, "Distributed=", osInfo.Distributed);
			TryFetchField(it, "ForegroundApplicationBoost=", osInfo.ForegroundApplicationBoost);
			TryFetchField(it, "FreePhysicalMemory=", osInfo.FreePhysicalMemory);
			TryFetchField(it, "FreeSpaceInPagingFiles=", osInfo.FreeSpaceInPagingFiles);
			TryFetchField(it, "FreeVirtualMemory=", osInfo.FreeVirtualMemory);
			TryFetchField(it, "Manufacturer=", osInfo.Manufacturer);
			TryFetchField(it, "MaxNumberOfProcesses=", osInfo.MaxNumberOfProcesses);
			TryFetchField(it, "MaxProcessMemorySize=", osInfo.MaxProcessMemorySize);
			TryFetchField(it, "OperatingSystemSKU=", osInfo.OperatingSystemSKU);
			TryFetchField(it, "OSArchitecture=", osInfo.OSArchitecture);
			TryFetchField(it, "OSProductSuite=", osInfo.OSProductSuite);
			TryFetchField(it, "OSType=", osInfo.OSType);
			TryFetchField(it, "PortableOperatingSystem=", osInfo.PortableOperatingSystem);
			TryFetchField(it, "Primary=", osInfo.Primary);
			TryFetchField(it, "ProductType=", osInfo.ProductType);
			TryFetchField(it, "SizeStoredInPagingFiles=", osInfo.SizeStoredInPagingFiles);
			TryFetchField(it, "Status=", osInfo.Status);
			TryFetchField(it, "SuiteMask=", osInfo.SuiteMask);
			TryFetchField(it, "TotalVirtualMemorySize=", osInfo.TotalVirtualMemorySize);
			TryFetchField(it, "TotalVisibleMemorySize=", osInfo.TotalVirtualMemorySize);
			TryFetchField(it, "Version=", osInfo.Version);

			if (it.find("Version=") == 0u)
			{
				osInfo.Index = index++;
				
				// store current os info then reset it
				ossInfo.push_back(osInfo);
				osInfo = Info();
			}
		}

		return ossInfo;
	}

	void FOS::TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue)
	{
		if (outValue != INFO_STR_UNKNOWN)
			return;

		outValue = iter.find(fieldName) != std::string::npos ? iter.substr(std::strlen(fieldName)) : INFO_STR_UNKNOWN;

		if (outValue == "")
			outValue = INFO_STR_UNKNOWN;
	}

}