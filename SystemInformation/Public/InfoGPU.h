#pragma once

#include "InfoBase.h"

#include <vector>

namespace SystemInfo {

    class SYSTEMINFORMATION_API FGPU
    {
    public:
		struct SYSTEMINFORMATION_API Info
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

			void LogToUE_LOG() const;
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