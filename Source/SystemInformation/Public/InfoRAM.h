#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

#include "InfoRAM.generated.h"

USTRUCT()
struct SYSTEMINFORMATION_API FRAMInformation
{
	GENERATED_BODY()

	UPROPERTY()
	FString Capacity = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString ConfiguredClockSpeed = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString ConfiguredVoltage = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString DataWidth = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString DeviceLocator = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString FormFactor = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString InterleaveDataDepth = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString InterleavePosition = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Manufacturer = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString MaxVoltage = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString MinVoltage = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString PartNumber = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString SMBIOSMemoryType = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Speed = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Tag = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString TotalWidth = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString TypeDetail = INFO_STR_UNKNOWN;

	UPROPERTY()
	int32 Index = 0u;

	void LogToUE_LOG() const;
};

class SYSTEMINFORMATION_API FRAMInformationFetcher
{
public:
	static TArray<FRAMInformation> FetchInfo();

private:
	static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);

	static const char* TranslateFormFactor(const FString& formFactor);
	static const char* TranslateSMBIOSMemoryType(const FString& smbiosMemoryType);
	static const char* TranslateTypeDetail(const FString& typeDetail);
};