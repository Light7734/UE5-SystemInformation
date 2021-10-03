#include "InfoOS.h"
#include "SystemCommand.h"

#define KILOBYTES_PER_MEGABYTE 1000

namespace SystemInfo {

	TArray<FOperatingSystem::Info> FOperatingSystem::FetchInfo()
	{
		// query operating-systems
		FSystemCommand operatingSystemsQuery("wmic path Win32_OperatingSystem get /format:list");

		if (operatingSystemsQuery.HasFailed())
		{
			UE_LOG(LogSystemInfo, Error, TEXT("Failed to query operating system"));
			return {};
		}

		// fetch operating-systems info
		TArray<Info> operatingSystemsInfo;
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

			if (it.Find("Version=") == 0u)
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
				operatingSystemsInfo.Push(operatingSystemInfo);
				operatingSystemInfo = Info();
			}
		}

		return operatingSystemsInfo;
	}

	void FOperatingSystem::TryFetchField(const FString& iter, const char* fieldName, FString& outValue)
	{
		if (outValue != INFO_STR_UNKNOWN)
			return;

		outValue = iter.Find(fieldName) == 0u ? iter.RightChop(std::strlen(fieldName)) : INFO_STR_UNKNOWN;

		if (outValue == "")
			outValue = INFO_STR_UNKNOWN;
	}

	const char* FOperatingSystem::TranslateDataExecutionPrevention_SupportPolicy(const FString& dataExecutionPrevention_SupportPolicy)
	{
		try
		{
			switch (FCString::Atoi(*dataExecutionPrevention_SupportPolicy))
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
			UE_LOG(LogTemp, Error, TEXT("Failed to translate operating system DataExecutionPrevention_SupportPolicy: %s"), *dataExecutionPrevention_SupportPolicy);
			return "";
		}
	}

	const char* FOperatingSystem::TranslateForegroundApplicationBoost(const FString& foregroundApplicationBoost)
	{
		try
		{
			switch (FCString::Atoi(*foregroundApplicationBoost))
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
			UE_LOG(LogTemp, Error, TEXT("Failed to translate operating system foreground application boost: %s"), *foregroundApplicationBoost);
			return "";
		}
	}

	const char* FOperatingSystem::TranslateProductType(const FString& productType)
	{
		
		try
		{
			switch (FCString::Atoi(*productType))
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
			UE_LOG(LogTemp, Error, TEXT("Failed to translate operating system product type: %s"), *productType);
			return "";
		}
	}


	void FOperatingSystem::Info::LogToUE_LOG() const
	{
		UE_LOG(LogSystemInfo, Log, TEXT("Operating System #%i {"), Index);
		UE_LOG(LogSystemInfo, Log, TEXT("    BuildNumber = %s"), *BuildNumber);
		UE_LOG(LogSystemInfo, Log, TEXT("    BuildType = %s"), *BuildType);
		UE_LOG(LogSystemInfo, Log, TEXT("    DataExecutionPrevention_32BitApplications = %s"), *DataExecutionPrevention_32BitApplications);
		UE_LOG(LogSystemInfo, Log, TEXT("    DataExecutionPrevention_Available = %s"), *DataExecutionPrevention_Available);
		UE_LOG(LogSystemInfo, Log, TEXT("    DataExecutionPrevention_Drivers = %s"), *DataExecutionPrevention_Drivers);
		UE_LOG(LogSystemInfo, Log, TEXT("    DataExecutionPrevention_SupportPolicy = %s"), *DataExecutionPrevention_SupportPolicy);
		UE_LOG(LogSystemInfo, Log, TEXT("    Distributed = %s"), *Distributed);
		UE_LOG(LogSystemInfo, Log, TEXT("    ForegroundApplicationBoost = %s"), *ForegroundApplicationBoost);
		UE_LOG(LogSystemInfo, Log, TEXT("    FreePhysicalMemory = %s"), *FreePhysicalMemory);
		UE_LOG(LogSystemInfo, Log, TEXT("    FreeSpaceInPagingFiles = %s"), *FreeSpaceInPagingFiles);
		UE_LOG(LogSystemInfo, Log, TEXT("    FreeVirtualMemory = %s"), *FreeVirtualMemory);
		UE_LOG(LogSystemInfo, Log, TEXT("    Manufacturer = %s"), *Manufacturer);
		UE_LOG(LogSystemInfo, Log, TEXT("    MaxNumberOfProcesses = %s"), *MaxNumberOfProcesses);
		UE_LOG(LogSystemInfo, Log, TEXT("    MaxProcessMemorySize = %s"), *MaxProcessMemorySize);
		UE_LOG(LogSystemInfo, Log, TEXT("    OSArchitecture = %s"), *OSArchitecture);
		UE_LOG(LogSystemInfo, Log, TEXT("    PortableOperatingSystem = %s"), *PortableOperatingSystem);
		UE_LOG(LogSystemInfo, Log, TEXT("    Primary = %s"), *Primary);
		UE_LOG(LogSystemInfo, Log, TEXT("    ProductType = %s"), *ProductType);
		UE_LOG(LogSystemInfo, Log, TEXT("    Status = %s"), *Status);
		UE_LOG(LogSystemInfo, Log, TEXT("    TotalVirtualMemorySize = %s"), *TotalVirtualMemorySize);
		UE_LOG(LogSystemInfo, Log, TEXT("    TotalVisibleMemorySize = %s"), *TotalVisibleMemorySize);
		UE_LOG(LogSystemInfo, Log, TEXT("    Version = %s"), *Version);
		UE_LOG(LogSystemInfo, Log, TEXT("}"));
	}

}