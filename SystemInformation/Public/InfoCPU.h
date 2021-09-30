#pragma once

#include "InfoBase.h"

#include <vector>

namespace SystemInfo {

    class SYSTEMINFORMATION_API FCPU
    {
    public:
		struct SYSTEMINFORMATION_API Info
		{
			std::string Architecture = INFO_STR_UNKNOWN;
			std::string Availability = INFO_STR_UNKNOWN;
			std::string Caption = INFO_STR_UNKNOWN;
			std::string Characteristics = INFO_STR_UNKNOWN;
			std::string CpuStatus = INFO_STR_UNKNOWN;
			std::string CurrentClockSpeed = INFO_STR_UNKNOWN;
			std::string CurrentVoltage = INFO_STR_UNKNOWN;
			std::string Description = INFO_STR_UNKNOWN;
			std::string DeviceID = INFO_STR_UNKNOWN;
			std::string ExtClock = INFO_STR_UNKNOWN;
			std::string Family = INFO_STR_UNKNOWN;
			std::string L2CacheSize = INFO_STR_UNKNOWN;
			std::string L3CacheSize = INFO_STR_UNKNOWN;
			std::string LoadPercentage = INFO_STR_UNKNOWN;
			std::string Manufacturer = INFO_STR_UNKNOWN;
			std::string MaxClockSpeed = INFO_STR_UNKNOWN;
			std::string Name = INFO_STR_UNKNOWN;
			std::string NumberOfCores = INFO_STR_UNKNOWN;
			std::string NumberOfEnabledCore = INFO_STR_UNKNOWN;
			std::string NumberOfLogicalProcessors = INFO_STR_UNKNOWN;
			std::string SecondLevelAddressTranslationExtensions = INFO_STR_UNKNOWN;
			std::string SocketDesignation = INFO_STR_UNKNOWN;
			std::string Status = INFO_STR_UNKNOWN;
			std::string ThreadCount = INFO_STR_UNKNOWN;

			uint32_t Index;

			void LogToUE_LOG() const;
		};

    public:
		static std::vector<Info> FetchInfo();

    private:
		static void TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue);

		static const char* TranslateArchitecture(const std::string& architecture);
		static const char* TranslateAvailability(const std::string& availability);
		static const char* TranslateFamiliy(const std::string& family);
    };

}