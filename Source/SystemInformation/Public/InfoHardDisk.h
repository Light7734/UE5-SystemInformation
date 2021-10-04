#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

#include "InfoHardDisk.generated.h"

USTRUCT()
struct SYSTEMINFORMATION_API FHardDiskInformation
{
	GENERATED_BODY()

	UPROPERTY()
	FString BytesPerSector = INFO_STR_UNKNOWN;

	UPROPERTY()
	TArray<FString> Capabilities;

	UPROPERTY()
	FString Caption = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString FirmwareRevision = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString InterfaceType = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Manufacturer = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString MediaType = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Model = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString SectorsPerTrack = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString SerialNumber = INFO_STR_UNKNOWN;
	
	UPROPERTY()
	FString Size = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString TotalCylinders = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString TotalHeads = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString TotalSectors = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString TotalTracks = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString TracksPerCylinder = INFO_STR_UNKNOWN;

	UPROPERTY()
	int32 Index;

	void LogToUE_LOG() const;
};

class SYSTEMINFORMATION_API FHardDiskInformationFetcher
{
public:
	static TArray<FHardDiskInformation> FetchInfo();

private:
	static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);
	static void TryFetchArrayField(const FString& iter, const char* fieldName, TArray<FString>& outValue);

};