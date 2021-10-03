#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

namespace SystemInfo {
	
	class SYSTEMINFORMATION_API FHardDisk
	{
	public:
		struct SYSTEMINFORMATION_API Info
		{
			FString BytesPerSector = INFO_STR_UNKNOWN;
			TArray<FString> Capabilities;
			FString Caption = INFO_STR_UNKNOWN;
			FString FirmwareRevision = INFO_STR_UNKNOWN;
			FString InterfaceType = INFO_STR_UNKNOWN;
			FString Manufacturer = INFO_STR_UNKNOWN;
			FString MediaType = INFO_STR_UNKNOWN;
			FString Model = INFO_STR_UNKNOWN;
			FString SectorsPerTrack = INFO_STR_UNKNOWN;
			FString SerialNumber = INFO_STR_UNKNOWN;
			FString Size = INFO_STR_UNKNOWN;
			FString TotalCylinders = INFO_STR_UNKNOWN;
			FString TotalHeads = INFO_STR_UNKNOWN;
			FString TotalSectors = INFO_STR_UNKNOWN;
			FString TotalTracks = INFO_STR_UNKNOWN;
			FString TracksPerCylinder = INFO_STR_UNKNOWN;

			uint32_t Index;

			void LogToUE_LOG() const;
		};

	public:
		static TArray<Info> FetchInfo();

	private:
		static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);
		static void TryFetchArrayField(const FString& iter, const char* fieldName, TArray<FString>& outValue);

	};

}