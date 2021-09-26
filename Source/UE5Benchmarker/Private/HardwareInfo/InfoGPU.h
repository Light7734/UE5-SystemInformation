#pragma once

#include "InfoBase.h"

#include <vector>

namespace HardwareInfo {

    class FGPU
    {
    public:
		struct Info
		{
			std::string AdapterCompatibility = INFO_STR_UNKNOWN;
			std::string AdapterDACType = INFO_STR_UNKNOWN;
			std::string AdapterRAM = INFO_STR_UNKNOWN;
			std::string Availability = INFO_STR_UNKNOWN;
			std::string Caption = INFO_STR_UNKNOWN;
			std::string CurrentBitsPerPixel = INFO_STR_UNKNOWN;
			std::string CurrentHorizontalResolution = INFO_STR_UNKNOWN;
			std::string CurrentNumberOfColors = INFO_STR_UNKNOWN;
			std::string CurrentRefreshRate = INFO_STR_UNKNOWN;
			std::string CurrentScanMode = INFO_STR_UNKNOWN;
			std::string CurrentVerticalResolution = INFO_STR_UNKNOWN;
			std::string Description = INFO_STR_UNKNOWN;
			std::string DeviceID = INFO_STR_UNKNOWN;
			std::string DriverDate = INFO_STR_UNKNOWN;
			std::string DriverVersion = INFO_STR_UNKNOWN;
			std::string InfFilename = INFO_STR_UNKNOWN;
			std::string InfSection = INFO_STR_UNKNOWN;
			std::string InstalledDisplayDrivers = INFO_STR_UNKNOWN;
			std::string MaxRefreshRate = INFO_STR_UNKNOWN;
			std::string MinRefreshRate = INFO_STR_UNKNOWN;
			std::string Monochrome = INFO_STR_UNKNOWN;
			std::string Name = INFO_STR_UNKNOWN;
			std::string Status = INFO_STR_UNKNOWN;
			std::string VideoArchitecture = INFO_STR_UNKNOWN;
			std::string VideoMemoryType = INFO_STR_UNKNOWN;
			std::string VideoModeDescription = INFO_STR_UNKNOWN;
			std::string VideoProcessor = INFO_STR_UNKNOWN;

			uint32_t Index;

			void LogToUE_LOG() const
			{
				UE_LOG(LogTemp, Log, TEXT("GPU #%i {"), Index);
				UE_LOG(LogTemp, Log, TEXT("    AdapterCompatibility = %s"), *FString(AdapterCompatibility.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    AdapterDACType = %s"), *FString(AdapterDACType.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    AdapterRAM = %s"), *FString(AdapterRAM.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Availability = %s"), *FString(Availability.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Caption = %s"), *FString(Caption.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    CurrentBitsPerPixel = %s"), *FString(CurrentBitsPerPixel.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    CurrentHorizontalResolution = %s"), *FString(CurrentHorizontalResolution.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    CurrentNumberOfColors = %s"), *FString(CurrentNumberOfColors.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    CurrentRefreshRate = %s"), *FString(CurrentRefreshRate.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    CurrentScanMode = %s"), *FString(CurrentScanMode.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    CurrentVerticalResolution = %s"), *FString(CurrentVerticalResolution.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Description = %s"), *FString(Description.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    DeviceID = %s"), *FString(DeviceID.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    DriverDate = %s"), *FString(DriverDate.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    DriverVersion = %s"), *FString(DriverVersion.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    InfFilename = %s"), *FString(InfFilename.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    InfSection = %s"), *FString(InfSection.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    InstalledDisplayDrivers = %s"), *FString(InstalledDisplayDrivers.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    MaxRefreshRate = %s"), *FString(MaxRefreshRate.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    MinRefreshRate = %s"), *FString(MinRefreshRate.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Monochrome = %s"), *FString(Monochrome.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Name = %s"), *FString(Name.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Status = %s"), *FString(Status.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    VideoArchitecture = %s"), *FString(VideoArchitecture.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    VideoMemoryType = %s"), *FString(VideoMemoryType.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    VideoModeDescription = %s"), *FString(VideoModeDescription.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    VideoProcessor = %s"), *FString(VideoProcessor.c_str()));
				UE_LOG(LogTemp, Log, TEXT("}"));
			}
		};

    public:
		static std::vector<Info> FetchInfo();

    private:
		static void TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue);

		static const char* TranslateAvailability(const std::string& availability);
		static const char* TranslateCurrentScanMode(const std::string& currentScanMode);
		static const char* TranslateVideoArchitecture(const std::string& videoArchitecture);
        static const char* TranslateVideoMemoryType(const std::string& videoMemoryType);

		static const char* ConvertNColorsToBPP(const std::string& videoMemoryType);

    };

}