#include "InfoHardDisk.h"

#include "SystemCommand.h"

namespace SystemInfo {

	std::vector<FHardDisk::Info> FHardDisk::FetchInfo()
	{
		// query hard disks
		FSystemCommand hardDisksQuery("wmic path Win32_DiskDrive get /format: list");

		if (hardDisksQuery.HasFailed())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to query hard disks"));
			return {};
		}

		// fetch hard disks info
		std::vector<Info> hardDisksInfo;
		Info hardDiskInfo;

		uint32_t index = 1u;
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

			if (it.find("TracksPerCylinder=") == 0u)
			{
				hardDiskInfo.Index = index++;

				// convert values
				hardDiskInfo.Size = ConvertDataUnits(hardDiskInfo.Size, EDataUnit::Byte);


				// information that could be extracted from the 'wmic' command ends here
				// insert further instructions here
				// ...


				// store current hard-disk info then reset it
				hardDisksInfo.push_back(hardDiskInfo);
				hardDiskInfo = Info();
			}
		}

		return hardDisksInfo;
	}

	void FHardDisk::TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue)
	{
		if (outValue != INFO_STR_UNKNOWN)
			return;

		outValue = iter.find(fieldName) == 0u ? iter.substr(std::strlen(fieldName)) : INFO_STR_UNKNOWN;

		if (outValue == "")
			outValue = INFO_STR_UNKNOWN;
	}

	void FHardDisk::TryFetchArrayField(const std::string& iter, const char* fieldName, std::vector<std::string>& outValue)
	{
		if (!outValue.empty() || iter.empty())
			return;

		if (iter.find(fieldName) == 0u)
		{
			std::string fieldValues = iter.substr(iter.find('{') + 2, iter.find('}') - iter.find('{') - 3);

			size_t pos;
			while((pos = fieldValues.find("\",\"")) != std::string::npos)
			{
				outValue.push_back(fieldValues.substr(0, pos));
				fieldValues.erase(0, pos + 3);
			}

			outValue.push_back(fieldValues);
			return;
		}
	}

	DEFINE_LOG_CATEGORY_STATIC(SystemInfo, Log, All);
	void FHardDisk::Info::LogToUE_LOG() const
	{
		UE_LOG(SystemInfo, Log, TEXT("Hard Disk #%i {"), Index);
		UE_LOG(SystemInfo, Log, TEXT("    BytesPerSector = %s"), *FString(BytesPerSector.c_str()));

		UE_LOG(SystemInfo, Log, TEXT("    Capabilities {"), *FString(BytesPerSector.c_str()));
		for (const auto& it : Capabilities)
			UE_LOG(SystemInfo, Log, TEXT("        %s"), *FString(it.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    }"), *FString(BytesPerSector.c_str()));

		UE_LOG(SystemInfo, Log, TEXT("    Caption = %s"), *FString(Caption.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    FirmwareRevision = %s"), *FString(FirmwareRevision.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    InterfaceType = %s"), *FString(InterfaceType.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Manuafacturer = %s"), *FString(Manufacturer.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    MediaType = %s"), *FString(MediaType.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Model = %s"), *FString(Model.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    SectorsPerTrack = %s"), *FString(SectorsPerTrack.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    SerialNumber = %s"), *FString(SerialNumber.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Size = %s"), *FString(Size.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    TotalCylinders = %s"), *FString(TotalCylinders.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    TotalHeads = %s"), *FString(TotalHeads.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    TotalSectors = %s"), *FString(TotalSectors.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    TotalTracks = %s"), *FString(TotalTracks.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    TracksPerCylinder = %s"), *FString(TracksPerCylinder.c_str()));

		UE_LOG(SystemInfo, Log, TEXT("}"));
	}

}