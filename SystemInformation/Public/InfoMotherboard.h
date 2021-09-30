#pragma once

#include "InfoBase.h"

#include <vector>

namespace SystemInfo {

	class SYSTEMINFORMATION_API FMotherboard
	{
	public:
		struct SYSTEMINFORMATION_API Info
		{
			std::string Manufacturer = INFO_STR_UNKNOWN;
			std::string Product = INFO_STR_UNKNOWN;
			std::string Status = INFO_STR_UNKNOWN;
			std::string Version = INFO_STR_UNKNOWN;

			uint8_t Index = 0u;

			void LogToUE_LOG() const;
		};

	public:
		static std::vector<Info> FetchInfo();

	private:
		static void TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue);
	};

}