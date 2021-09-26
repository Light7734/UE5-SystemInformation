#include "InfoGPU.h"
#include "SystemCommand.h"

namespace HardwareInfo {

    std::vector<FGPU::Info> FGPU::FetchInfo()
    {
        // query gpus
        FSystemCommand gpusQuery("wmic path Win32_VideoController get /format: list");

        if (gpusQuery.HasFailed())
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to query GPUs"));
            return {};
        }

        // fetch gpus info
        std::vector<Info> gpusInfo;
        Info gpuInfo;
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

            if (it.find("VideoProcessor=") == 0u)
            {
                gpuInfo.Index = index;

                // store current gpu info then reset it
                gpusInfo.push_back(gpuInfo);
                gpuInfo = Info();
            }
        }

        return gpusInfo;
    }

	void FGPU::TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue)
	{
		if (outValue != INFO_STR_UNKNOWN)
			return;

		outValue = iter.find(fieldName) != std::string::npos ? iter.substr(std::strlen(fieldName)) : INFO_STR_UNKNOWN;

		if (outValue == "")
			outValue = INFO_STR_UNKNOWN;
	}

    const char* FGPU::DetermineVideoArchitecture(const std::string videoArchitectureStr)
    {
        int videoArchitecture = 2;

        try {
            videoArchitecture = std::stoi(videoArchitectureStr);
        }
        catch (std::exception& e) {
            (void)e;
            videoArchitecture = 2;
        }

        // https://msdn.microsoft.com/en-us/library/aa394512(v=vs.85).aspx
        switch (videoArchitecture) {
        case 1: return "Other";
        case 2: return UNKNOWN_INFO_STR;
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

    const char* FGPU::DetermineVideoMemoryType(const std::string& videoMemoryTypeStr)
    {
        int videoMemoryType = 2;

        try {
            videoMemoryType = std::stoi(videoMemoryTypeStr);
        }
        catch (std::exception& e) {
            (void)e;
            return UNKNOWN_INFO_STR;
        }

        switch (videoMemoryType)
        {
        case 1: return "Other";
        case 2: return UNKNOWN_INFO_STR;
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

}