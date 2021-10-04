#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

#include "InfoGPU.generated.h"

USTRUCT()
struct SYSTEMINFORMATION_API FGPUInformation
{
	GENERATED_BODY()

	UPROPERTY()
	FString AdapterCompatibility = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString AdapterDACType = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString AdapterRAM = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Availability = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Caption = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString CurrentBitsPerPixel = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString CurrentHorizontalResolution = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString CurrentNumberOfColors = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString CurrentRefreshRate = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString CurrentScanMode = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString CurrentVerticalResolution = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Description = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString DeviceID = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString DriverDate = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString DriverVersion = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString InfFilename = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString InfSection = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString InstalledDisplayDrivers = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString MaxRefreshRate = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString MinRefreshRate = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Monochrome = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Name = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Status = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString VideoArchitecture = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString VideoMemoryType = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString VideoModeDescription = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString VideoProcessor = INFO_STR_UNKNOWN;

	UPROPERTY()
	int32 Index;

	void LogToUE_LOG() const;
};

class SYSTEMINFORMATION_API FGPUInformationFetcher
{

public:
	static TArray<FGPUInformation> FetchInfo();

private:
	static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);

	static const char* TranslateAvailability(const FString& availability);
	static const char* TranslateCurrentScanMode(const FString& currentScanMode);
	static const char* TranslateVideoArchitecture(const FString& videoArchitecture);
    static const char* TranslateVideoMemoryType(const FString& videoMemoryType);
};