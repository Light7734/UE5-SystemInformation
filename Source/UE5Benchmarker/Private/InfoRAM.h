#pragma once

#include "InfoBase.h"

#include <vector>

namespace HardwareInfo {

	class FRAM
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

			uint8_t Index = 0u;
		};

	public:
		static std::vector<Info> FetchInfo();

	private:
		static void FetchField(const std::string& iter, const char* fieldName, std::string& outValue);

		static std::string DetermineMemoryType(const std::string& memoryTypeString);
		static std::string DetermineFormFactor(const std::string& formFactorString);
	};

}