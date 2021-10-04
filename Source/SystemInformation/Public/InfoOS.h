#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

#include "InfoOS.generated.h"

USTRUCT()
struct SYSTEMINFORMATION_API FOperatingSystemInformation
{
	GENERATED_BODY()

	UPROPERTY()
	FString BuildNumber = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString BuildType = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Caption = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString DataExecutionPrevention_32BitApplications = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString DataExecutionPrevention_Available = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString DataExecutionPrevention_Drivers = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString DataExecutionPrevention_SupportPolicy = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Distributed = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString ForegroundApplicationBoost = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString FreePhysicalMemory = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString FreeSpaceInPagingFiles = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString FreeVirtualMemory = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Manufacturer = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString MaxNumberOfProcesses = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString MaxProcessMemorySize = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString OSArchitecture = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString PortableOperatingSystem = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Primary = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString ProductType = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString SizeStoredInPagingFiles = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Status = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString TotalVirtualMemorySize = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString TotalVisibleMemorySize = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Version = INFO_STR_UNKNOWN;

	uint32_t Index;

	void LogToUE_LOG() const;
};


class SYSTEMINFORMATION_API FOperatingSystemInformationFetcher
{
public:
	static TArray<FOperatingSystemInformation> FetchInfo();

private:
	static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);

	static const char* TranslateDataExecutionPrevention_SupportPolicy(const FString& dataExecutionPrevention_SupportPolicy);
	static const char* TranslateForegroundApplicationBoost(const FString& foregroundApplicationBoost);
	static const char* TranslateProductType(const FString& productType);

};