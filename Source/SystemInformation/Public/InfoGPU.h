#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

namespace SystemInfo {

    class SYSTEMINFORMATION_API FGPU
    {
    public:
		struct SYSTEMINFORMATION_API Info
		{
			FString AdapterCompatibility = INFO_STR_UNKNOWN;
			FString AdapterDACType = INFO_STR_UNKNOWN;
			FString AdapterRAM = INFO_STR_UNKNOWN;
			FString Availability = INFO_STR_UNKNOWN;
			FString Caption = INFO_STR_UNKNOWN;
			FString CurrentBitsPerPixel = INFO_STR_UNKNOWN;
			FString CurrentHorizontalResolution = INFO_STR_UNKNOWN;
			FString CurrentNumberOfColors = INFO_STR_UNKNOWN;
			FString CurrentRefreshRate = INFO_STR_UNKNOWN;
			FString CurrentScanMode = INFO_STR_UNKNOWN;
			FString CurrentVerticalResolution = INFO_STR_UNKNOWN;
			FString Description = INFO_STR_UNKNOWN;
			FString DeviceID = INFO_STR_UNKNOWN;
			FString DriverDate = INFO_STR_UNKNOWN;
			FString DriverVersion = INFO_STR_UNKNOWN;
			FString InfFilename = INFO_STR_UNKNOWN;
			FString InfSection = INFO_STR_UNKNOWN;
			FString InstalledDisplayDrivers = INFO_STR_UNKNOWN;
			FString MaxRefreshRate = INFO_STR_UNKNOWN;
			FString MinRefreshRate = INFO_STR_UNKNOWN;
			FString Monochrome = INFO_STR_UNKNOWN;
			FString Name = INFO_STR_UNKNOWN;
			FString Status = INFO_STR_UNKNOWN;
			FString VideoArchitecture = INFO_STR_UNKNOWN;
			FString VideoMemoryType = INFO_STR_UNKNOWN;
			FString VideoModeDescription = INFO_STR_UNKNOWN;
			FString VideoProcessor = INFO_STR_UNKNOWN;

			uint32_t Index;

			void LogToUE_LOG() const;
		};

    public:
		static TArray<Info> FetchInfo();

    private:
		static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);

		static const char* TranslateAvailability(const FString& availability);
		static const char* TranslateCurrentScanMode(const FString& currentScanMode);
		static const char* TranslateVideoArchitecture(const FString& videoArchitecture);
        static const char* TranslateVideoMemoryType(const FString& videoMemoryType);
    };

}