#include "InfoMotherboard.h"
#include "SystemCommand.h"

// #define CHIPSET_QUERY_STRING "wmic path Win32_PnPEntity get /format:list | findstr /R /C:\"Chipset\""

namespace SystemInfo {

	std::vector<FMotherboard::Info> FMotherboard::FetchInfo()
	{
		// query motherboards
		FSystemCommand motherboardsQuery("wmic path Win32_BaseBoard get /format: list");

		if (motherboardsQuery.HasFailed())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to quety motherboard(s)"));
			return {};
		}

		// fetch motherboards info
		std::vector<Info> motherboardsInfo;
		Info motherboardInfo;

		uint32_t index = 1u;
		for (const auto& it : motherboardsQuery.GetResult())
		{
			TryFetchField(it, "Manufacturer=", motherboardInfo.Manufacturer);
			TryFetchField(it, "Product=", motherboardInfo.Product);
			TryFetchField(it, "Status=", motherboardInfo.Status);
			TryFetchField(it, "Version=", motherboardInfo.Version);

			if (it.find("Version=") == 0u)
			{
				motherboardInfo.Index = index++;


				// information that could be extracted from the 'wmic' command ends here
                // insert further instructions here
                // ...


				// store current motherboard info then reset it
				motherboardsInfo.push_back(motherboardInfo);
				motherboardInfo = Info();
			}
		}

		return motherboardsInfo;
	}

	void FMotherboard::TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue)
	{
		if (outValue != INFO_STR_UNKNOWN)
			return;

		outValue = iter.find(fieldName) == 0u ? iter.substr(iter.find(fieldName) + std::strlen(fieldName)) : INFO_STR_UNKNOWN;

		if (outValue == "")
			outValue = INFO_STR_UNKNOWN;
	}

}