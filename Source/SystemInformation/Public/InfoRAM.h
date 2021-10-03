#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

namespace SystemInfo {

	class SYSTEMINFORMATION_API FRAM
	{
	public:
		struct SYSTEMINFORMATION_API Info
		{
			FString Capacity = INFO_STR_UNKNOWN;
			FString ConfiguredClockSpeed = INFO_STR_UNKNOWN;
			FString ConfiguredVoltage = INFO_STR_UNKNOWN;
			FString DataWidth = INFO_STR_UNKNOWN;
			FString DeviceLocator = INFO_STR_UNKNOWN;
			FString FormFactor = INFO_STR_UNKNOWN;
			FString InterleaveDataDepth = INFO_STR_UNKNOWN;
			FString InterleavePosition = INFO_STR_UNKNOWN;
			FString Manufacturer = INFO_STR_UNKNOWN;
			FString MaxVoltage = INFO_STR_UNKNOWN;
			FString MinVoltage = INFO_STR_UNKNOWN;
			FString PartNumber = INFO_STR_UNKNOWN;
			FString SMBIOSMemoryType = INFO_STR_UNKNOWN;
			FString Speed = INFO_STR_UNKNOWN;
			FString Tag = INFO_STR_UNKNOWN;
			FString TotalWidth = INFO_STR_UNKNOWN;
			FString TypeDetail = INFO_STR_UNKNOWN;

			uint32_t Index = 0u;

			void LogToUE_LOG() const;
		};

	public:
		static TArray<Info> FetchInfo();

	private:
		static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);

		static const char* TranslateFormFactor(const FString& formFactor);
		static const char* TranslateSMBIOSMemoryType(const FString& smbiosMemoryType);
		static const char* TranslateTypeDetail(const FString& typeDetail);
	};

}