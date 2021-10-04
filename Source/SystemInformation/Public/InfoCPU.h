#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

#include "InfoCPU.generated.h"

USTRUCT()
struct SYSTEMINFORMATION_API FCPUInformation
{
	GENERATED_BODY()

	UPROPERTY()
	FString Architecture = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Availability = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Caption = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Characteristics = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString CpuStatus = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString CurrentClockSpeed = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString CurrentVoltage = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Description = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString DeviceID = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString ExtClock = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Family = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString L2CacheSize = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString L3CacheSize = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString LoadPercentage = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Manufacturer = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString MaxClockSpeed = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Name = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString NumberOfCores = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString NumberOfEnabledCore = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString NumberOfLogicalProcessors = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString SecondLevelAddressTranslationExtensions = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString SocketDesignation = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Status = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString ThreadCount = INFO_STR_UNKNOWN;

	UPROPERTY()
	int32 Index;

	void LogToUE_LOG() const;
};

class SYSTEMINFORMATION_API FCPUInformationFetcher
{
public:
	static TArray<FCPUInformation> FetchInfo();

private:
	static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);

	static const char* TranslateArchitecture(const FString& architecture);
	static const char* TranslateAvailability(const FString& availability);
	static const char* TranslateFamiliy(const FString& family);
};
