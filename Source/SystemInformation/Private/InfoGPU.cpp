#include "InfoGPU.h"
#include "SystemCommand.h"

#include <Logging/LogMacros.h>

TArray<FGPUInformation> FGPUInformationFetcher::FetchInfo()
{
	// query gpus
	FSystemCommand gpusQuery("wmic path Win32_VideoController get /format: list");

	if (gpusQuery.HasFailed())
	{
		UE_LOG(LogSystemInfo, Error, TEXT("Failed to query GPUs"));
		return {};
	}

	// fetch gpus info
	TArray<FGPUInformation> gpusInfo;
	FGPUInformation gpuInfo;
	uint32_t index = 1u;

	for (const auto& it : gpusQuery.GetResult())
	{
		TryFetchField(it, "AdapterCompatibility=", gpuInfo.AdapterCompatibility);
		TryFetchField(it, "AdapterDACType=", gpuInfo.AdapterDACType);
		TryFetchField(it, "AdapterRAM=", gpuInfo.AdapterRAM);
		TryFetchField(it, "Availability=", gpuInfo.Availability);
		TryFetchField(it, "Caption=", gpuInfo.Caption);
		TryFetchField(it, "CurrentBitsPerPixel=", gpuInfo.CurrentBitsPerPixel);
		TryFetchField(it, "CurrentHorizontalResolution=", gpuInfo.CurrentHorizontalResolution);
		TryFetchField(it, "CurrentNumberOfColors=", gpuInfo.CurrentNumberOfColors);
		TryFetchField(it, "CurrentRefreshRate=", gpuInfo.CurrentRefreshRate);
		TryFetchField(it, "CurrentScanMode=", gpuInfo.CurrentScanMode);
		TryFetchField(it, "CurrentVerticalResolution=", gpuInfo.CurrentVerticalResolution);
		TryFetchField(it, "Description=", gpuInfo.Description);
		TryFetchField(it, "DeviceID=", gpuInfo.DeviceID);
		TryFetchField(it, "DriverDate=", gpuInfo.DriverDate);
		TryFetchField(it, "DriverVersion=", gpuInfo.DriverVersion);
		TryFetchField(it, "InfFilename=", gpuInfo.InfFilename);
		TryFetchField(it, "InfSection=", gpuInfo.InfSection);
		TryFetchField(it, "InstalledDisplayDrivers=", gpuInfo.InstalledDisplayDrivers);
		TryFetchField(it, "MaxRefreshRate=", gpuInfo.MaxRefreshRate);
		TryFetchField(it, "MinRefreshRate=", gpuInfo.MinRefreshRate);
		TryFetchField(it, "Monochrome=", gpuInfo.Monochrome);
		TryFetchField(it, "Name=", gpuInfo.Name);
		TryFetchField(it, "Status=", gpuInfo.Status);
		TryFetchField(it, "VideoArchitecture=", gpuInfo.VideoArchitecture);
		TryFetchField(it, "VideoMemoryType=", gpuInfo.VideoMemoryType);
		TryFetchField(it, "VideoModeDescription=", gpuInfo.VideoModeDescription);
		TryFetchField(it, "VideoProcessor=", gpuInfo.VideoProcessor);

		if (it.Find("VideoProcessor=") == 0u)
		{
			gpuInfo.Index = index;

			// translate enum values
			gpuInfo.Availability = TranslateAvailability(gpuInfo.Availability);
			gpuInfo.CurrentScanMode = TranslateCurrentScanMode(gpuInfo.CurrentScanMode);
			gpuInfo.VideoArchitecture = TranslateVideoArchitecture(gpuInfo.VideoArchitecture);
			gpuInfo.VideoMemoryType = TranslateVideoMemoryType(gpuInfo.VideoMemoryType);

			// convert values
			gpuInfo.AdapterRAM = ConvertDataUnits(gpuInfo.AdapterRAM, ESystemInfoDataUnit::Byte);


			// information that could be extracted from the 'wmic' command ends here
			// insert further instructions here
			// ...


			// store current gpu info then reset it
			gpusInfo.Push(gpuInfo);
			gpuInfo = FGPUInformation();
		}
	}


	return gpusInfo;
}

void FGPUInformationFetcher::TryFetchField(const FString& iter, const char* fieldName, FString& outValue)
{
	if (outValue != INFO_STR_UNKNOWN)
		return;

	outValue = iter.Find(fieldName) == 0u ? iter.RightChop(std::strlen(fieldName)) : INFO_STR_UNKNOWN;

	if (outValue == "")
		outValue = INFO_STR_UNKNOWN;
}

const char* FGPUInformationFetcher::TranslateAvailability(const FString& availability)
{
	try
	{
		switch (FCString::Atoi(*availability))
		{
		case 1: return "Other";
		case 2: return "Unknown";
		case 3: return "Running/Full Power";
		case 4: return "Warning";
		case 5: return "In Test";
		case 6: return "Not Applicable";
		case 7: return "Power Off";
		case 8: return "Off Line";
		case 9: return "Off Duty";
		case 10: return "Degraded";
		case 11: return "Not Installed";
		case 12: return "Install Error";
		case 13: return "Power Save - Unknown";
		case 14: return "Power Save - Low Power Mode";
		case 15: return "Power Save - Standby";
		case 16: return "Power Cycle";
		case 17: return "Power Save - Warning";
		case 18: return "Paused";
		case 19: return "Not Ready";
		case 20: return "Not Configured";
		case 21: return "Quiesced";
		default: return INFO_STR_UNKNOWN;
		}
	}
	catch (std::exception e)
	{
		(void)e;
		UE_LOG(LogTemp, Error, TEXT("Failed to translate gpu availability: %s"), *availability);
		return "";
	}
}

const char* FGPUInformationFetcher::TranslateCurrentScanMode(const FString& currentScanMode)
{
	try
	{
		switch (FCString::Atoi(*currentScanMode))
		{
		case 1: return "Other";
		case 2: return "Unknown";
		case 3: return "Interlaced";
		case 4: return "Non Interlaced";
		default: return INFO_STR_UNKNOWN;
		}
	}
	catch (std::exception e)
	{
		(void)e;
		UE_LOG(LogTemp, Error, TEXT("Failed to translate gpu current scan mode: %s"), *currentScanMode);
		return "";
	}
}

const char* FGPUInformationFetcher::TranslateVideoArchitecture(const FString& videoArchitecture)
{
	try
	{

		switch (FCString::Atoi(*videoArchitecture))
		{
		case 1: return "Other";
		case 2: return "Unknown";
		case 3: return "CGA";
		case 4: return "EGA";
		case 5: return "VGA";
		case 6: return "SVGA";
		case 7: return "MDA";
		case 8: return "HGC";
		case 9: return "MCGA";
		case 10: return "8514A";
		case 11: return "XGA";
		case 12: return "Linear Frame Buffer";
		case 160: return "PC - 98";
		default: return INFO_STR_UNKNOWN;
		}
	}
	catch (std::exception e)
	{
		(void)e;
		UE_LOG(LogTemp, Error, TEXT("Failed to translate gpu video architecture: %s"), *videoArchitecture);
		return "";
	}
}

const char* FGPUInformationFetcher::TranslateVideoMemoryType(const FString& videoMemoryType)
{
	try
	{
		switch (FCString::Atoi(*videoMemoryType))
		{
		case 1: return "Other";
		case 2: return "Unknown";
		case 3: return "VRAM";
		case 4: return "DRAM";
		case 5: return "SRAM";
		case 6: return "WRAM";
		case 7: return "EDO_RAM";
		case 8: return "Burst Synchronous DRAM";
		case 9: return "Pipelined Burst SRAM";
		case 10: return "CDRAM";
		case 11: return "3DRAM";
		case 12: return "SDRAM";
		case 13: return "SGRAM";
		default: return INFO_STR_UNKNOWN;
		}
	}
	catch (std::exception e)
	{
		(void)e;
		UE_LOG(LogTemp, Error, TEXT("Failed to translate gpu video memory type: %s"), *videoMemoryType);
		return "";
	}
}

void FGPUInformation::LogToUE_LOG() const
{
	UE_LOG(LogSystemInfo, Log, TEXT("GPU #%i {"), Index);
	UE_LOG(LogSystemInfo, Log, TEXT("    AdapterCompatibility = %s"), *AdapterCompatibility);
	UE_LOG(LogSystemInfo, Log, TEXT("    AdapterDACType = %s"), *AdapterDACType);
	UE_LOG(LogSystemInfo, Log, TEXT("    AdapterRAM = %s"), *AdapterRAM);
	UE_LOG(LogSystemInfo, Log, TEXT("    Availability = %s"), *Availability);
	UE_LOG(LogSystemInfo, Log, TEXT("    Caption = %s"), *Caption);
	UE_LOG(LogSystemInfo, Log, TEXT("    CurrentBitsPerPixel = %s"), *CurrentBitsPerPixel);
	UE_LOG(LogSystemInfo, Log, TEXT("    CurrentHorizontalResolution = %s"), *CurrentHorizontalResolution);
	UE_LOG(LogSystemInfo, Log, TEXT("    CurrentNumberOfColors = %s"), *CurrentNumberOfColors);
	UE_LOG(LogSystemInfo, Log, TEXT("    CurrentRefreshRate = %s"), *CurrentRefreshRate);
	UE_LOG(LogSystemInfo, Log, TEXT("    CurrentScanMode = %s"), *CurrentScanMode);
	UE_LOG(LogSystemInfo, Log, TEXT("    CurrentVerticalResolution = %s"), *CurrentVerticalResolution);
	UE_LOG(LogSystemInfo, Log, TEXT("    Description = %s"), *Description);
	UE_LOG(LogSystemInfo, Log, TEXT("    DeviceID = %s"), *DeviceID);
	UE_LOG(LogSystemInfo, Log, TEXT("    DriverDate = %s"), *DriverDate);
	UE_LOG(LogSystemInfo, Log, TEXT("    DriverVersion = %s"), *DriverVersion);
	UE_LOG(LogSystemInfo, Log, TEXT("    InfFilename = %s"), *InfFilename);
	UE_LOG(LogSystemInfo, Log, TEXT("    InfSection = %s"), *InfSection);
	UE_LOG(LogSystemInfo, Log, TEXT("    InstalledDisplayDrivers = %s"), *InstalledDisplayDrivers);
	UE_LOG(LogSystemInfo, Log, TEXT("    MaxRefreshRate = %s"), *MaxRefreshRate);
	UE_LOG(LogSystemInfo, Log, TEXT("    MinRefreshRate = %s"), *MinRefreshRate);
	UE_LOG(LogSystemInfo, Log, TEXT("    Monochrome = %s"), *Monochrome);
	UE_LOG(LogSystemInfo, Log, TEXT("    Name = %s"), *Name);
	UE_LOG(LogSystemInfo, Log, TEXT("    Status = %s"), *Status);
	UE_LOG(LogSystemInfo, Log, TEXT("    VideoArchitecture = %s"), *VideoArchitecture);
	UE_LOG(LogSystemInfo, Log, TEXT("    VideoMemoryType = %s"), *VideoMemoryType);
	UE_LOG(LogSystemInfo, Log, TEXT("    VideoModeDescription = %s"), *VideoModeDescription);
	UE_LOG(LogSystemInfo, Log, TEXT("    VideoProcessor = %s"), *VideoProcessor);
	UE_LOG(LogSystemInfo, Log, TEXT("}"));
}