#pragma once

#include "InfoBase.h"

#include <vector>

namespace HardwareInfo {

	class SYSTEMINFORMATION_API FOperatingSystem
	{
	public:
		struct Info
		{
			std::string BuildNumber = INFO_STR_UNKNOWN;
			std::string BuildType = INFO_STR_UNKNOWN;
			std::string Caption = INFO_STR_UNKNOWN;
			std::string DataExecutionPrevention_32BitApplications = INFO_STR_UNKNOWN;
			std::string DataExecutionPrevention_Available = INFO_STR_UNKNOWN;
			std::string DataExecutionPrevention_Drivers = INFO_STR_UNKNOWN;
			std::string DataExecutionPrevention_SupportPolicy = INFO_STR_UNKNOWN;
			std::string Distributed = INFO_STR_UNKNOWN;
			std::string ForegroundApplicationBoost = INFO_STR_UNKNOWN;
			std::string FreePhysicalMemory = INFO_STR_UNKNOWN;
			std::string FreeSpaceInPagingFiles = INFO_STR_UNKNOWN;
			std::string FreeVirtualMemory = INFO_STR_UNKNOWN;
			std::string Manufacturer = INFO_STR_UNKNOWN;
			std::string MaxNumberOfProcesses = INFO_STR_UNKNOWN;
			std::string MaxProcessMemorySize = INFO_STR_UNKNOWN;
			std::string OSArchitecture = INFO_STR_UNKNOWN;
			std::string PortableOperatingSystem = INFO_STR_UNKNOWN;
			std::string Primary = INFO_STR_UNKNOWN;
			std::string ProductType = INFO_STR_UNKNOWN;
			std::string SizeStoredInPagingFiles = INFO_STR_UNKNOWN;
			std::string Status = INFO_STR_UNKNOWN;
			std::string TotalVirtualMemorySize = INFO_STR_UNKNOWN;
			std::string TotalVisibleMemorySize = INFO_STR_UNKNOWN;
			std::string Version = INFO_STR_UNKNOWN;

			uint32_t Index;

			void LogToUE_LOG() const
			{
				UE_LOG(LogTemp, Log, TEXT("Operating System #%i {"), Index);
				UE_LOG(LogTemp, Log, TEXT("    BuildNumber = %s"), *FString(BuildNumber.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    BuildType = %s"), *FString(BuildType.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    DataExecutionPrevention_32BitApplications = %s"), *FString(DataExecutionPrevention_32BitApplications.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    DataExecutionPrevention_Available = %s"), *FString(DataExecutionPrevention_Available.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    DataExecutionPrevention_Drivers = %s"), *FString(DataExecutionPrevention_Drivers.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    DataExecutionPrevention_SupportPolicy = %s"), *FString(DataExecutionPrevention_SupportPolicy.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Distributed = %s"), *FString(Distributed.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    ForegroundApplicationBoost = %s"), *FString(ForegroundApplicationBoost.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    FreePhysicalMemory = %s"), *FString(FreePhysicalMemory.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    FreeSpaceInPagingFiles = %s"), *FString(FreeSpaceInPagingFiles.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    FreeVirtualMemory = %s"), *FString(FreeVirtualMemory.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Manufacturer = %s"), *FString(Manufacturer.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    MaxNumberOfProcesses = %s"), *FString(MaxNumberOfProcesses.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    MaxProcessMemorySize = %s"), *FString(MaxProcessMemorySize.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    OSArchitecture = %s"), *FString(OSArchitecture.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    PortableOperatingSystem = %s"), *FString(PortableOperatingSystem.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Primary = %s"), *FString(Primary.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    ProductType = %s"), *FString(ProductType.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Status = %s"), *FString(Status.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    TotalVirtualMemorySize = %s"), *FString(TotalVirtualMemorySize.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    TotalVisibleMemorySize = %s"), *FString(TotalVisibleMemorySize.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Version = %s"), *FString(Version.c_str()));
				UE_LOG(LogTemp, Log, TEXT("}"));
			}
		};

	public:
		static std::vector<Info> FetchInfo();

	private:
		static void TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue);

		static const char* TranslateDataExecutionPrevention_SupportPolicy(const std::string& dataExecutionPrevention_SupportPolicy);
		static const char* TranslateForegroundApplicationBoost(const std::string& foregroundApplicationBoost);
		static const char* TranslateProductType(const std::string& productType);

	};

}