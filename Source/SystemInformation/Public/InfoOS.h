#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

namespace SystemInfo {

	class SYSTEMINFORMATION_API FOperatingSystem
	{
	public:
		struct SYSTEMINFORMATION_API Info
		{
			FString BuildNumber = INFO_STR_UNKNOWN;
			FString BuildType = INFO_STR_UNKNOWN;
			FString Caption = INFO_STR_UNKNOWN;
			FString DataExecutionPrevention_32BitApplications = INFO_STR_UNKNOWN;
			FString DataExecutionPrevention_Available = INFO_STR_UNKNOWN;
			FString DataExecutionPrevention_Drivers = INFO_STR_UNKNOWN;
			FString DataExecutionPrevention_SupportPolicy = INFO_STR_UNKNOWN;
			FString Distributed = INFO_STR_UNKNOWN;
			FString ForegroundApplicationBoost = INFO_STR_UNKNOWN;
			FString FreePhysicalMemory = INFO_STR_UNKNOWN;
			FString FreeSpaceInPagingFiles = INFO_STR_UNKNOWN;
			FString FreeVirtualMemory = INFO_STR_UNKNOWN;
			FString Manufacturer = INFO_STR_UNKNOWN;
			FString MaxNumberOfProcesses = INFO_STR_UNKNOWN;
			FString MaxProcessMemorySize = INFO_STR_UNKNOWN;
			FString OSArchitecture = INFO_STR_UNKNOWN;
			FString PortableOperatingSystem = INFO_STR_UNKNOWN;
			FString Primary = INFO_STR_UNKNOWN;
			FString ProductType = INFO_STR_UNKNOWN;
			FString SizeStoredInPagingFiles = INFO_STR_UNKNOWN;
			FString Status = INFO_STR_UNKNOWN;
			FString TotalVirtualMemorySize = INFO_STR_UNKNOWN;
			FString TotalVisibleMemorySize = INFO_STR_UNKNOWN;
			FString Version = INFO_STR_UNKNOWN;

			uint32_t Index;

			void LogToUE_LOG() const;
		};

	public:
		static TArray<Info> FetchInfo();

	private:
		static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);

		static const char* TranslateDataExecutionPrevention_SupportPolicy(const FString& dataExecutionPrevention_SupportPolicy);
		static const char* TranslateForegroundApplicationBoost(const FString& foregroundApplicationBoost);
		static const char* TranslateProductType(const FString& productType);

	};

}