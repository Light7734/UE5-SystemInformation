#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

namespace SystemInfo {

    class SYSTEMINFORMATION_API FCPU
    {
    public:
		struct SYSTEMINFORMATION_API Info
		{
			FString Architecture = INFO_STR_UNKNOWN;
			FString Availability = INFO_STR_UNKNOWN;
			FString Caption = INFO_STR_UNKNOWN;
			FString Characteristics = INFO_STR_UNKNOWN;
			FString CpuStatus = INFO_STR_UNKNOWN;
			FString CurrentClockSpeed = INFO_STR_UNKNOWN;
			FString CurrentVoltage = INFO_STR_UNKNOWN;
			FString Description = INFO_STR_UNKNOWN;
			FString DeviceID = INFO_STR_UNKNOWN;
			FString ExtClock = INFO_STR_UNKNOWN;
			FString Family = INFO_STR_UNKNOWN;
			FString L2CacheSize = INFO_STR_UNKNOWN;
			FString L3CacheSize = INFO_STR_UNKNOWN;
			FString LoadPercentage = INFO_STR_UNKNOWN;
			FString Manufacturer = INFO_STR_UNKNOWN;
			FString MaxClockSpeed = INFO_STR_UNKNOWN;
			FString Name = INFO_STR_UNKNOWN;
			FString NumberOfCores = INFO_STR_UNKNOWN;
			FString NumberOfEnabledCore = INFO_STR_UNKNOWN;
			FString NumberOfLogicalProcessors = INFO_STR_UNKNOWN;
			FString SecondLevelAddressTranslationExtensions = INFO_STR_UNKNOWN;
			FString SocketDesignation = INFO_STR_UNKNOWN;
			FString Status = INFO_STR_UNKNOWN;
			FString ThreadCount = INFO_STR_UNKNOWN;
			uint32_t Index;

			void LogToUE_LOG() const;
		};

    public:
		static TArray<Info> FetchInfo();

    private:
		static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);

		static const char* TranslateArchitecture(const FString& architecture);
		static const char* TranslateAvailability(const FString& availability);
		static const char* TranslateFamiliy(const FString& family);
    };

}