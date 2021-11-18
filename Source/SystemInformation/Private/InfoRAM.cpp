#include "InfoRAM.h"
#include "systemcommand.h"

TArray<FRAMInformation> FRAMInformationFetcher::FetchInfo()
{
	// query rams
	FSystemCommand ramsQuery("wmic path Win32_PhysicalMemory get /format: list");
	if (ramsQuery.HasFailed())
	{
		UE_LOG(LogSystemInfo, Error, TEXT("Failed to query RAMs"));
		return {};
	}

	// fetch rams info
	TArray<FRAMInformation> ramsInfo;
	FRAMInformation ramInfo;

	int32 index = 1u;
	for (auto it : ramsQuery.GetResult())
	{
		TryFetchField(it, "Capacity=", ramInfo.Capacity);
		TryFetchField(it, "ConfiguredClockSpeed=", ramInfo.ConfiguredClockSpeed);
		TryFetchField(it, "ConfiguredVoltage=", ramInfo.ConfiguredVoltage);
		TryFetchField(it, "DataWidth=", ramInfo.DataWidth);
		TryFetchField(it, "DeviceLocator=", ramInfo.DeviceLocator);
		TryFetchField(it, "FormFactor=", ramInfo.FormFactor);
		TryFetchField(it, "InterleaveDataDepth=", ramInfo.InterleaveDataDepth);
		TryFetchField(it, "InterleavePosition=", ramInfo.InterleavePosition);
		TryFetchField(it, "Manufacturer=", ramInfo.Manufacturer);
		TryFetchField(it, "MaxVoltage=", ramInfo.MaxVoltage);
		TryFetchField(it, "MinVoltage=", ramInfo.MinVoltage);
		TryFetchField(it, "PartNumber=", ramInfo.PartNumber);
		TryFetchField(it, "SMBIOSMemoryType=", ramInfo.SMBIOSMemoryType);
		TryFetchField(it, "Speed=", ramInfo.Speed);
		TryFetchField(it, "Tag=", ramInfo.Tag);
		TryFetchField(it, "TotalWidth=", ramInfo.TotalWidth);
		TryFetchField(it, "TypeDetail=", ramInfo.TypeDetail);

		if (it.Find("Version") == 0u)
		{
			ramInfo.Index = index++;

			// translate enum values
			ramInfo.FormFactor = TranslateFormFactor(ramInfo.FormFactor);
			ramInfo.SMBIOSMemoryType = TranslateFormFactor(ramInfo.SMBIOSMemoryType);
			ramInfo.TypeDetail = TranslateFormFactor(ramInfo.TypeDetail);

			// convert values
			ramInfo.Capacity = ConvertDataUnits(ramInfo.Capacity, ESystemInfoDataUnit::Byte);


			// information that could be extracted from the 'wmic' command ends here
			// insert further instructions here
			// ...


			// store current ram info then reset it
			ramsInfo.Push(ramInfo);
			ramInfo = FRAMInformation();
		}
	}

	return ramsInfo;
}

void FRAMInformationFetcher::TryFetchField(const FString& iter, const char* fieldName, FString& outValue)
{
	if (outValue != INFO_STR_UNKNOWN)
		return;

	outValue = iter.Find(fieldName) == 0u ? iter.RightChop(iter.Find(fieldName) + std::strlen(fieldName)) : INFO_STR_UNKNOWN;

	if (outValue == "")
		outValue = INFO_STR_UNKNOWN;
}


const char* FRAMInformationFetcher::TranslateFormFactor(const FString& formFactor)
{
	try
	{
		switch (FCString::Atoi(*formFactor)) {
		case 0: return "Unknown";
		case 1: return "Other";
		case 2: return "SIP";
		case 3: return "DIP";
		case 4: return "ZIP";
		case 5: return "SOJ";
		case 6: return "Proprietary";
		case 7: return "SIMM";
		case 8: return "DIMM";
		case 9: return "TSOP";
		case 10: return "PGA";
		case 11: return "RIMM";
		case 12: return "SODIMM";
		case 13: return "SRIMM";
		case 14: return "SMD";
		case 15: return "SSMP";
		case 16: return "QFD";
		case 17: return "TQFP";
		case 18: return "SOIC";
		case 19: return "LCC";
		case 20: return "PLCC";
		case 21: return "BGA";
		case 22: return "FPBGA";
		case 23: return "LGA";
		default: return INFO_STR_UNKNOWN;
		}
	}
	catch (std::exception& e)
	{
		(void)e;
		UE_LOG(LogTemp, Error, TEXT("Failed to translate ram form factor: %s"), *formFactor);
		return "";
	}
}

const char* FRAMInformationFetcher::TranslateSMBIOSMemoryType(const FString& smbiosMemoryType)
{
	try
	{
		switch (FCString::Atoi(*smbiosMemoryType))
		{
		case 0: return "Unknown";
		case 1: return "Other";
		case 2: return "DRAM";
		case 3: return "Synchronous DRAM";
		case 4: return "Cache DRAM";
		case 5: return "EDO";
		case 6: return "EDRAM";
		case 7: return "VRAM";
		case 8: return "SRAM";
		case 9: return "RAM";
		case 10: return "ROM";
		case 11: return "Flash";
		case 12: return "EEPROM";
		case 13: return "FEPROM";
		case 14: return "EPROM";
		case 15: return "CDRAM";
		case 16: return "3DRAM";
		case 17: return "SDRAM";
		case 18: return "SGRAM";
		case 19: return "RDRAM";
		case 20: return "DDR1";
		case 21: return "DDR2";
		case 22: return "DDR2 - FBDIMM";
		case 23: return "DDR2 - FBDIMM";
		case 24: return "DDR3";
		case 25: return "FBD2";
		case 26: return "DDR4";
		default: return INFO_STR_UNKNOWN;
		}
	}
	catch (std::exception& e)
	{
		(void)e;
		UE_LOG(LogTemp, Error, TEXT("Failed to translate smbios memory type: %s"), *smbiosMemoryType);
		return "";
	}
}


const char* FRAMInformationFetcher::TranslateTypeDetail(const FString& typeDetail)
{
	try
	{
		switch (FCString::Atoi(*typeDetail))
		{
		case 1: return "Reserved";
		case 2: return "Other";
		case 4: return "Unknown";
		case 8: return "Fast-paged";
		case 16: return "Static column";
		case 32: return "Pseudo-static";
		case 64: return "RAMBUS";
		case 128: return "Synchronous";
		case 256: return "CMOS";
		case 512: return "EDO";
		case 1024: return "Window DRAM";
		case 2048: return "Cache DRAM";
		case 4096: return "Non-volatile";
		default: return INFO_STR_UNKNOWN;
		}
	}
	catch (std::exception& e)
	{
		(void)e;
		UE_LOG(LogTemp, Error, TEXT("Failed to translate type detail: %s"), *typeDetail);
		return "";
	}
}


void FRAMInformation::LogToUE_LOG() const
{
	UE_LOG(LogSystemInfo, Log, TEXT("RAM #%i {"), Index);
	UE_LOG(LogSystemInfo, Log, TEXT("    Capacity = %s"), *Capacity);
	UE_LOG(LogSystemInfo, Log, TEXT("    ConfiguredClockSpeed = %s"), *ConfiguredClockSpeed);
	UE_LOG(LogSystemInfo, Log, TEXT("    ConfiguredVoltage = %s"), *ConfiguredVoltage);
	UE_LOG(LogSystemInfo, Log, TEXT("    DataWidth = %s"), *DataWidth);
	UE_LOG(LogSystemInfo, Log, TEXT("    DeviceLocator = %s"), *DeviceLocator);
	UE_LOG(LogSystemInfo, Log, TEXT("    FormFactor = %s"), *FormFactor);
	UE_LOG(LogSystemInfo, Log, TEXT("    InterleaveDataDepth = %s"), *InterleaveDataDepth);
	UE_LOG(LogSystemInfo, Log, TEXT("    InterleavePosition = %s"), *InterleavePosition);
	UE_LOG(LogSystemInfo, Log, TEXT("    Manufacturer = %s"), *Manufacturer);
	UE_LOG(LogSystemInfo, Log, TEXT("    MaxVoltage = %s"), *MaxVoltage);
	UE_LOG(LogSystemInfo, Log, TEXT("    MinVoltage = %s"), *MinVoltage);
	UE_LOG(LogSystemInfo, Log, TEXT("    PartNumber = %s"), *PartNumber);
	UE_LOG(LogSystemInfo, Log, TEXT("    MinVoltage = %s"), *MinVoltage);
	UE_LOG(LogSystemInfo, Log, TEXT("    SMBIOSMemoryType = %s"), *SMBIOSMemoryType);
	UE_LOG(LogSystemInfo, Log, TEXT("    Speed = %s"), *Speed);
	UE_LOG(LogSystemInfo, Log, TEXT("    Tag = %s"), *Tag);
	UE_LOG(LogSystemInfo, Log, TEXT("    TotalWidth = %s"), *TotalWidth);
	UE_LOG(LogSystemInfo, Log, TEXT("    TypeDetail = %s"), *TypeDetail);
	UE_LOG(LogSystemInfo, Log, TEXT("}"));
}