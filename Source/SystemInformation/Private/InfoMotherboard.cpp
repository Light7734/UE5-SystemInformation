#include "InfoMotherboard.h"
#include "SystemCommand.h"

TArray<FMotherboardInformation> FMotherboardInformationFetcher::FetchInfo()
{
	// query motherboards
	FSystemCommand motherboardsQuery("wmic path Win32_BaseBoard get /format: list");

	if (motherboardsQuery.HasFailed())
	{
		UE_LOG(LogSystemInfo, Error, TEXT("Failed to quety motherboard(s)"));
		return {};
	}

	// fetch motherboards info
	TArray<FMotherboardInformation> motherboardsInfo;
	FMotherboardInformation motherboardInfo;

	int32 index = 1u;
	for (const auto& it : motherboardsQuery.GetResult())
	{
		TryFetchField(it, "Manufacturer=", motherboardInfo.Manufacturer);
		TryFetchField(it, "Product=", motherboardInfo.Product);
		TryFetchField(it, "Status=", motherboardInfo.Status);
		TryFetchField(it, "Version=", motherboardInfo.Version);

		if (it.Find("Version=") == 0u)
		{
			motherboardInfo.Index = index++;


			// information that could be extracted from the 'wmic' command ends here
			// insert further instructions here
			// ...


			// store current motherboard info then reset it
			motherboardsInfo.Push(motherboardInfo);
			motherboardInfo = FMotherboardInformation();
		}
	}

	return motherboardsInfo;
}

void FMotherboardInformationFetcher::TryFetchField(const FString& iter, const char* fieldName, FString& outValue)
{
	if (outValue != INFO_STR_UNKNOWN)
		return;

	outValue = iter.Find(fieldName) == 0u ? iter.RightChop(iter.Find(fieldName) + std::strlen(fieldName)) : INFO_STR_UNKNOWN;

	if (outValue == "")
		outValue = INFO_STR_UNKNOWN;
}


void FMotherboardInformation::LogToUE_LOG() const
{
	UE_LOG(LogSystemInfo, Log, TEXT("Motherboard #%i {"), Index);
	UE_LOG(LogSystemInfo, Log, TEXT("    Manufacturer = %s"), *Manufacturer);
	UE_LOG(LogSystemInfo, Log, TEXT("    Product = %s"), *Product);
	UE_LOG(LogSystemInfo, Log, TEXT("    Status = %s"), *Status);
	UE_LOG(LogSystemInfo, Log, TEXT("    Version = %s"), *Version);
	UE_LOG(LogSystemInfo, Log, TEXT("}"));
}

