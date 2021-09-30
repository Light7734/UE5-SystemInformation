#pragma once

#include "InfoBase.h"

#include <vector>

namespace SystemInfo {
	
	class SYSTEMINFORMATION_API FHardDisk
	{
	public:
		struct SYSTEMINFORMATION_API Info
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

			void LogToUE_LOG() const;
		};

	public:
		static std::vector<Info> FetchInfo();

	private:
		static void TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue);
		static void TryFetchArrayField(const std::string& iter, const char* fieldName, std::vector<std::string>& outValue);

	};

}