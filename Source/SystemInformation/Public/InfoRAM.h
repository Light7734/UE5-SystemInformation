#pragma once

#include "InfoBase.h"

#include <vector>

namespace HardwareInfo {

	class SYSTEMINFORMATION_API FRAM
	{
	public:
		struct Info
		{
			std::string Capacity = INFO_STR_UNKNOWN;
			std::string ConfiguredClockSpeed = INFO_STR_UNKNOWN;
			std::string ConfiguredVoltage = INFO_STR_UNKNOWN;
			std::string DataWidth = INFO_STR_UNKNOWN;
			std::string DeviceLocator = INFO_STR_UNKNOWN;
			std::string FormFactor = INFO_STR_UNKNOWN;
			std::string InterleaveDataDepth = INFO_STR_UNKNOWN;
			std::string InterleavePosition = INFO_STR_UNKNOWN;
			std::string Manufacturer = INFO_STR_UNKNOWN;
			std::string MaxVoltage = INFO_STR_UNKNOWN;
			std::string MinVoltage = INFO_STR_UNKNOWN;
			std::string PartNumber = INFO_STR_UNKNOWN;
			std::string SMBIOSMemoryType = INFO_STR_UNKNOWN;
			std::string Speed = INFO_STR_UNKNOWN;
			std::string Tag = INFO_STR_UNKNOWN;
			std::string TotalWidth = INFO_STR_UNKNOWN;
			std::string TypeDetail = INFO_STR_UNKNOWN;

			uint32_t Index = 0u;

			void LogToUE_LOG() const
			{
				UE_LOG(LogTemp, Log, TEXT("RAM #%i {"), Index);
				UE_LOG(LogTemp, Log, TEXT("    Capacity = %s"), *FString(Capacity.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    ConfiguredClockSpeed = %s"), *FString(ConfiguredClockSpeed.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    ConfiguredVoltage = %s"), *FString(ConfiguredVoltage.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    DataWidth = %s"), *FString(DataWidth.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    DeviceLocator = %s"), *FString(DeviceLocator.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    FormFactor = %s"), *FString(FormFactor.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    InterleaveDataDepth = %s"), *FString(InterleaveDataDepth.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    InterleavePosition = %s"), *FString(InterleavePosition.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Manufacturer = %s"), *FString(Manufacturer.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    MaxVoltage = %s"), *FString(MaxVoltage.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    MinVoltage = %s"), *FString(MinVoltage.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    PartNumber = %s"), *FString(PartNumber.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    MinVoltage = %s"), *FString(MinVoltage.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    SMBIOSMemoryType = %s"), *FString(SMBIOSMemoryType.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Speed = %s"), *FString(Speed.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Tag = %s"), *FString(Tag.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    TotalWidth = %s"), *FString(TotalWidth.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    TypeDetail = %s"), *FString(TypeDetail.c_str()));
				UE_LOG(LogTemp, Log, TEXT("}"));
			}
		};

	public:
		static std::vector<Info> FetchInfo();

	private:
		static void TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue);

		static const char* TranslateFormFactor(const std::string& formFactor);
		static const char* TranslateSMBIOSMemoryType(const std::string& smbiosMemoryType);
		static const char* TranslateTypeDetail(const std::string& typeDetail);
	};

}