#pragma once

#include "InfoBase.h"

#include <vector>

namespace SystemInfo {

    class SYSTEMINFORMATION_API FCPU
    {
    public:
		struct Info
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

			void LogToUE_LOG() const
			{
				UE_LOG(LogTemp, Log, TEXT("CPU #%i {"), Index);
				UE_LOG(LogTemp, Log, TEXT("    Architecture = %s"), *FString(Architecture.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Availability = %s"), *FString(Availability.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Caption = %s"), *FString(Caption.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Characteristics = %s"), *FString(Characteristics.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    CpuStatus = %s"), *FString(CpuStatus.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    CurrentClockSpeed = %s"), *FString(CurrentClockSpeed.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    CurrentVoltage = %s"), *FString(CurrentVoltage.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Description = %s"), *FString(Description.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    DeviceID = %s"), *FString(DeviceID.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    ExtClock = %s"), *FString(ExtClock.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Family = %s"), *FString(Family.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    L2CacheSize = %s"), *FString(L2CacheSize.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    L3CacheSize = %s"), *FString(L3CacheSize.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    LoadPercentage = %s"), *FString(LoadPercentage.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Manufacturer = %s"), *FString(Manufacturer.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    MaxClockSpeed = %s"), *FString(MaxClockSpeed.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    NumberOfCores = %s"), *FString(NumberOfCores.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    NumberOfEnabledCore = %s"), *FString(NumberOfEnabledCore.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    NumberOfLogicalProcessors = %s"), *FString(NumberOfLogicalProcessors.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    SecondLevelAddressTranslationExtensions = %s"), *FString(SecondLevelAddressTranslationExtensions.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    SocketDesignation = %s"), *FString(SocketDesignation.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Status = %s"), *FString(Status.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    ThreadCount = %s"), *FString(ThreadCount.c_str()));
				UE_LOG(LogTemp, Log, TEXT("}"));
			}
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