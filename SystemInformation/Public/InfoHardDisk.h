#pragma once

#include "InfoBase.h"

#include <vector>

namespace SystemInfo {
	
	class SYSTEMINFORMATION_API FHardDisk
	{
	public:
		struct Info
		{
			std::string BytesPerSector = INFO_STR_UNKNOWN;
			std::vector<std::string> Capabilities;
			std::string Caption = INFO_STR_UNKNOWN;
			std::string FirmwareRevision = INFO_STR_UNKNOWN;
			std::string InterfaceType = INFO_STR_UNKNOWN;
			std::string Manufacturer = INFO_STR_UNKNOWN;
			std::string MediaType = INFO_STR_UNKNOWN;
			std::string Model = INFO_STR_UNKNOWN;
			std::string SectorsPerTrack = INFO_STR_UNKNOWN;
			std::string SerialNumber = INFO_STR_UNKNOWN;
			std::string Size = INFO_STR_UNKNOWN;
			std::string TotalCylinders = INFO_STR_UNKNOWN;
			std::string TotalHeads = INFO_STR_UNKNOWN;
			std::string TotalSectors = INFO_STR_UNKNOWN;
			std::string TotalTracks = INFO_STR_UNKNOWN;
			std::string TracksPerCylinder = INFO_STR_UNKNOWN;

			uint32_t Index;

			void LogToUE_LOG() const
			{
				UE_LOG(LogTemp, Log, TEXT("Hard Disk #%i {"), Index);
				UE_LOG(LogTemp, Log, TEXT("    BytesPerSector = %s"), *FString(BytesPerSector.c_str()));

				UE_LOG(LogTemp, Log, TEXT("    Capabilities {"), *FString(BytesPerSector.c_str()));
				for(const auto& it : Capabilities)
					UE_LOG(LogTemp, Log, TEXT("        %s"), *FString(it.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    }"), *FString(BytesPerSector.c_str()));

				UE_LOG(LogTemp, Log, TEXT("    Caption = %s"), *FString(Caption.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    FirmwareRevision = %s"), *FString(FirmwareRevision.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    InterfaceType = %s"), *FString(InterfaceType.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Manuafacturer = %s"), *FString(Manufacturer.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    MediaType = %s"), *FString(MediaType.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Model = %s"), *FString(Model.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    SectorsPerTrack = %s"), *FString(SectorsPerTrack.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    SerialNumber = %s"), *FString(SerialNumber.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Size = %s"), *FString(Size.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    TotalCylinders = %s"), *FString(TotalCylinders.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    TotalHeads = %s"), *FString(TotalHeads.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    TotalSectors = %s"), *FString(TotalSectors.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    TotalTracks = %s"), *FString(TotalTracks.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    TracksPerCylinder = %s"), *FString(TracksPerCylinder.c_str()));

				UE_LOG(LogTemp, Log, TEXT("}"));
			}

		};

	public:
		static std::vector<Info> FetchInfo();

	private:
		static void TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue);
		static void TryFetchArrayField(const std::string& iter, const char* fieldName, std::vector<std::string>& outValue);

	};

}