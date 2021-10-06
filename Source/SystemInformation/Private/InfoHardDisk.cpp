#include "InfoHardDisk.h"

#include "SystemCommand.h"

TArray<FHardDiskInformation> FHardDiskInformationFetcher::FetchInfo()
{
	// query hard disks
	FSystemCommand hardDisksQuery("wmic path Win32_DiskDrive get /format: list");

	if (hardDisksQuery.HasFailed())
	{
		UE_LOG(LogSystemInfo, Error, TEXT("Failed to query hard disks"));
		return {};
	}

	// fetch hard disks info
	TArray<FHardDiskInformation> hardDisksInfo;
	FHardDiskInformation hardDiskInfo;

	int32 index = 1u;
	for (const auto& it : hardDisksQuery.GetResult())
	{
		TryFetchField(it, "BytesPerSector=", hardDiskInfo.BytesPerSector);
		TryFetchField(it, "Caption=", hardDiskInfo.Caption);
		TryFetchField(it, "FirmwareRevision=", hardDiskInfo.FirmwareRevision);
		TryFetchField(it, "InterfaceType=", hardDiskInfo.InterfaceType);
		TryFetchField(it, "Manufacturer=", hardDiskInfo.Manufacturer);
		TryFetchField(it, "MediaType=", hardDiskInfo.MediaType);
		TryFetchField(it, "Model=", hardDiskInfo.Model);
		TryFetchField(it, "SectorsPerTrack=", hardDiskInfo.SectorsPerTrack);
		TryFetchField(it, "SerialNumber=", hardDiskInfo.SerialNumber);
		TryFetchField(it, "Size=", hardDiskInfo.Size);
		TryFetchField(it, "TotalCylinders=", hardDiskInfo.TotalCylinders);
		TryFetchField(it, "TotalHeads=", hardDiskInfo.TotalHeads);
		TryFetchField(it, "TotalSectors=", hardDiskInfo.TotalSectors);
		TryFetchField(it, "TotalTracks=", hardDiskInfo.TotalTracks);
		TryFetchField(it, "TracksPerCylinder=", hardDiskInfo.TracksPerCylinder);

		TryFetchArrayField(it, "CapabilityDescriptions=", hardDiskInfo.Capabilities);

		if (it.Find("TracksPerCylinder=") == 0u)
		{
			hardDiskInfo.Index = index++;

			// convert values
			hardDiskInfo.Size = ConvertDataUnits(hardDiskInfo.Size, ESysdtemInfoDataUnit::Byte);


			// information that could be extracted from the 'wmic' command ends here
			// insert further instructions here
			// ...


			// store current hard-disk info then reset it
			hardDisksInfo.Push(hardDiskInfo);
			hardDiskInfo = FHardDiskInformation();
		}
	}

	return hardDisksInfo;
}

void FHardDiskInformationFetcher::TryFetchField(const FString& iter, const char* fieldName, FString& outValue)
{
	if (outValue != INFO_STR_UNKNOWN)
		return;

	outValue = iter.Find(fieldName) == 0u ? iter.RightChop(std::strlen(fieldName)) : INFO_STR_UNKNOWN;

	if (outValue == "")
		outValue = INFO_STR_UNKNOWN;
}

void FHardDiskInformationFetcher::TryFetchArrayField(const FString& iter, const char* fieldName, TArray<FString>& outValue)
{
	if (!outValue.IsEmpty() || iter.IsEmpty())
		return;

	if (iter.Find(fieldName) == 0u)
	{
		FString fieldValues = iter.Mid(iter.Find("{") + 2, iter.Find("}") - iter.Find("{") - 3);

		size_t pos;
		while ((pos = fieldValues.Find("\",\"")) != std::string::npos)
		{
			outValue.Push(fieldValues.Mid(0u, pos));
			fieldValues.RemoveAt(0, pos + 3);
		}

		outValue.Push(fieldValues);
		return;
	}
}

void FHardDiskInformation::LogToUE_LOG() const
{
	UE_LOG(LogSystemInfo, Log, TEXT("Hard Disk #%i {"), Index);
	UE_LOG(LogSystemInfo, Log, TEXT("    BytesPerSector = %s"), *BytesPerSector);

	UE_LOG(LogSystemInfo, Log, TEXT("    Capabilities {"), *BytesPerSector);
	for (const auto& it : Capabilities)
		UE_LOG(LogSystemInfo, Log, TEXT("        %s"), *it);
	UE_LOG(LogSystemInfo, Log, TEXT("    }"), *BytesPerSector);

	UE_LOG(LogSystemInfo, Log, TEXT("    Caption = %s"), *Caption);
	UE_LOG(LogSystemInfo, Log, TEXT("    FirmwareRevision = %s"), *FirmwareRevision);
	UE_LOG(LogSystemInfo, Log, TEXT("    InterfaceType = %s"), *InterfaceType);
	UE_LOG(LogSystemInfo, Log, TEXT("    Manuafacturer = %s"), *Manufacturer);
	UE_LOG(LogSystemInfo, Log, TEXT("    MediaType = %s"), *MediaType);
	UE_LOG(LogSystemInfo, Log, TEXT("    Model = %s"), *Model);
	UE_LOG(LogSystemInfo, Log, TEXT("    SectorsPerTrack = %s"), *SectorsPerTrack);
	UE_LOG(LogSystemInfo, Log, TEXT("    SerialNumber = %s"), *SerialNumber);
	UE_LOG(LogSystemInfo, Log, TEXT("    Size = %s"), *Size);
	UE_LOG(LogSystemInfo, Log, TEXT("    TotalCylinders = %s"), *TotalCylinders);
	UE_LOG(LogSystemInfo, Log, TEXT("    TotalHeads = %s"), *TotalHeads);
	UE_LOG(LogSystemInfo, Log, TEXT("    TotalSectors = %s"), *TotalSectors);
	UE_LOG(LogSystemInfo, Log, TEXT("    TotalTracks = %s"), *TotalTracks);
	UE_LOG(LogSystemInfo, Log, TEXT("    TracksPerCylinder = %s"), *TracksPerCylinder);

	UE_LOG(LogSystemInfo, Log, TEXT("}"));
}