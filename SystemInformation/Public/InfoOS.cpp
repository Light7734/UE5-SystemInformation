#include "InfoOS.h"
#include "SystemCommand.h"

#define KILOBYTES_PER_MEGABYTE 1000

namespace SystemInfo {

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
			TryFetchField(it, "TotalVisibleMemorySize=", operatingSystemInfo.TotalVisibleMemorySize);
			TryFetchField(it, "Version=", operatingSystemInfo.Version);

			if (it.find("Version=") == 0u)
			{
				operatingSystemInfo.Index = index++;
				
				// translate enum types
				operatingSystemInfo.DataExecutionPrevention_SupportPolicy = TranslateDataExecutionPrevention_SupportPolicy(operatingSystemInfo.DataExecutionPrevention_SupportPolicy);
				operatingSystemInfo.ForegroundApplicationBoost = TranslateForegroundApplicationBoost(operatingSystemInfo.ForegroundApplicationBoost);
				operatingSystemInfo.ProductType = TranslateProductType(operatingSystemInfo.ProductType);

				// convert values
				operatingSystemInfo.FreePhysicalMemory = ConvertDataUnits(operatingSystemInfo.FreePhysicalMemory, EDataUnit::KiloByte);
				operatingSystemInfo.FreeSpaceInPagingFiles = ConvertDataUnits(operatingSystemInfo.FreeSpaceInPagingFiles, EDataUnit::KiloByte);
				operatingSystemInfo.FreeVirtualMemory = ConvertDataUnits(operatingSystemInfo.FreeVirtualMemory, EDataUnit::KiloByte);
				operatingSystemInfo.MaxProcessMemorySize = ConvertDataUnits(operatingSystemInfo.MaxProcessMemorySize, EDataUnit::KiloByte);
				operatingSystemInfo.TotalVirtualMemorySize = ConvertDataUnits(operatingSystemInfo.TotalVirtualMemorySize, EDataUnit::KiloByte);
				operatingSystemInfo.TotalVisibleMemorySize = ConvertDataUnits(operatingSystemInfo.TotalVisibleMemorySize, EDataUnit::KiloByte);


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


	DEFINE_LOG_CATEGORY_STATIC(SystemInfo, Log, All);
	void FOperatingSystem::Info::LogToUE_LOG() const
	{
		UE_LOG(SystemInfo, Log, TEXT("Operating System #%i {"), Index);
		UE_LOG(SystemInfo, Log, TEXT("    BuildNumber = %s"), *FString(BuildNumber.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    BuildType = %s"), *FString(BuildType.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    DataExecutionPrevention_32BitApplications = %s"), *FString(DataExecutionPrevention_32BitApplications.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    DataExecutionPrevention_Available = %s"), *FString(DataExecutionPrevention_Available.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    DataExecutionPrevention_Drivers = %s"), *FString(DataExecutionPrevention_Drivers.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    DataExecutionPrevention_SupportPolicy = %s"), *FString(DataExecutionPrevention_SupportPolicy.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Distributed = %s"), *FString(Distributed.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    ForegroundApplicationBoost = %s"), *FString(ForegroundApplicationBoost.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    FreePhysicalMemory = %s"), *FString(FreePhysicalMemory.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    FreeSpaceInPagingFiles = %s"), *FString(FreeSpaceInPagingFiles.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    FreeVirtualMemory = %s"), *FString(FreeVirtualMemory.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Manufacturer = %s"), *FString(Manufacturer.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    MaxNumberOfProcesses = %s"), *FString(MaxNumberOfProcesses.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    MaxProcessMemorySize = %s"), *FString(MaxProcessMemorySize.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    OSArchitecture = %s"), *FString(OSArchitecture.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    PortableOperatingSystem = %s"), *FString(PortableOperatingSystem.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Primary = %s"), *FString(Primary.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    ProductType = %s"), *FString(ProductType.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Status = %s"), *FString(Status.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    TotalVirtualMemorySize = %s"), *FString(TotalVirtualMemorySize.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    TotalVisibleMemorySize = %s"), *FString(TotalVisibleMemorySize.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Version = %s"), *FString(Version.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("}"));
	}

}