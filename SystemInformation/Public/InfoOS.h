#pragma once

#include "InfoBase.h"

#include <vector>

namespace SystemInfo {

	class SYSTEMINFORMATION_API FOperatingSystem
	{
	public:
		struct SYSTEMINFORMATION_API Info
		{
			std::string BuildNumber = INFO_STR_UNKNOWN;
			std::string BuildType = INFO_STR_UNKNOWN;
			std::string Caption = INFO_STR_UNKNOWN;
			std::string DataExecutionPrevention_32BitApplications = INFO_STR_UNKNOWN;
			std::string DataExecutionPrevention_Available = INFO_STR_UNKNOWN;
			std::string DataExecutionPrevention_Drivers = INFO_STR_UNKNOWN;
			std::string DataExecutionPrevention_SupportPolicy = INFO_STR_UNKNOWN;
			std::string Distributed = INFO_STR_UNKNOWN;
			std::string ForegroundApplicationBoost = INFO_STR_UNKNOWN;
			std::string FreePhysicalMemory = INFO_STR_UNKNOWN;
			std::string FreeSpaceInPagingFiles = INFO_STR_UNKNOWN;
			std::string FreeVirtualMemory = INFO_STR_UNKNOWN;
			std::string Manufacturer = INFO_STR_UNKNOWN;
			std::string MaxNumberOfProcesses = INFO_STR_UNKNOWN;
			std::string MaxProcessMemorySize = INFO_STR_UNKNOWN;
			std::string OSArchitecture = INFO_STR_UNKNOWN;
			std::string PortableOperatingSystem = INFO_STR_UNKNOWN;
			std::string Primary = INFO_STR_UNKNOWN;
			std::string ProductType = INFO_STR_UNKNOWN;
			std::string SizeStoredInPagingFiles = INFO_STR_UNKNOWN;
			std::string Status = INFO_STR_UNKNOWN;
			std::string TotalVirtualMemorySize = INFO_STR_UNKNOWN;
			std::string TotalVisibleMemorySize = INFO_STR_UNKNOWN;
			std::string Version = INFO_STR_UNKNOWN;

			uint32_t Index;

			void LogToUE_LOG() const;
		};

	public:
		static std::vector<Info> FetchInfo();

	private:
		static void TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue);

		static const char* TranslateDataExecutionPrevention_SupportPolicy(const std::string& dataExecutionPrevention_SupportPolicy);
		static const char* TranslateForegroundApplicationBoost(const std::string& foregroundApplicationBoost);
		static const char* TranslateProductType(const std::string& productType);

	};

}