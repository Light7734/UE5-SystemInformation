#include "InfoGPU.h"
#include "SystemCommand.h"

#define NVIDIA_IDENTIFIER_STRING "NVIDIA"
#define INTEL_IDENTIFIER_STRING "INTEL"
#define AMD_IDENTIFIER_STRING "AMD"
#define NAME_IDENTIFIER_STRING "Name="
#define MANUFACTURER_IDENTIFIER_STRING "AdapterCompatibility="
#define ADAPTER_RAM_IDENTIFIER_STRING "AdapterRAM="
#define REFRESH_RATE_IDENTIFIER_STRING "CurrentRefreshRate="
#define DRIVER_VERSION_IDENTIFIER_STRING "DriverVersion="
#define VIDEO_ARCHITECTURE_IDENTIFIER_STRING "VideoArchitecture="
#define VIDEO_MEMORY_TYPE_IDENTIFIER_STRING "VideoMemoryType"
#define VIDEO_MODE_DESCRIPTION_IDENTIFIER_STRING "VideoModeDescription="
#define VIDEO_PROCESSOR_IDENTIFIER_STRING "VideoProcessor="
#define CAPTION_IDENTIFIER_STRING "Caption="

#define GPU_INFO_QUERY_STRING "wmic path Win32_VideoController get /format: list"
#define GPU_INSTANCE_QUERY_STRING "CurrentBitsPerPixel="
#define GPU_INFO_END_IDENTIFIER_STRING "VideoProcessor="

FGPUInfoCollector::FGPUInfoCollector()
    : GPUCount(0)
{
	FSystemCommand GPUsQuery(GPU_INFO_QUERY_STRING);

    if (GPUsQuery.HasFailed())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to query GPUs"));
        return;
    }

	// Fetch GPU count
	for (const auto iter : GPUsQuery)
		if (iter.find(GPU_INSTANCE_QUERY_STRING) != std::string::npos) 
			GPUCount++;

    if (!GPUCount)
        UE_LOG(LogTemp, Error, TEXT("No GPUs found"));

    for (uint8_t i = 0u; i < GPUCount; i++)
    {
        FGPUInfo GPUInfo;
        GPUInfo.Index = i + 1;

		for (auto iter = GPUsQuery.GetResult().begin(); iter->find(GPU_INFO_END_IDENTIFIER_STRING) == std::string::npos; iter++)
		{
			// Name
			if (FIND_IN_ITER(NAME_IDENTIFIER_STRING))
				GPUInfo.Name = iter->substr(iter->find(NAME_IDENTIFIER_STRING) + std::strlen(NAME_IDENTIFIER_STRING));

			// Manufacturer
			if (FIND_IN_ITER(MANUFACTURER_IDENTIFIER_STRING))
				GPUInfo.Manufacturer = iter->substr(iter->find(MANUFACTURER_IDENTIFIER_STRING) + std::strlen(MANUFACTURER_IDENTIFIER_STRING));

			// Caption
			if (FIND_IN_ITER(CAPTION_IDENTIFIER_STRING))
				GPUInfo.Caption = iter->substr(iter->find(CAPTION_IDENTIFIER_STRING) + std::strlen(CAPTION_IDENTIFIER_STRING));

			// Adapter RAM
			if ((iter->find(ADAPTER_RAM_IDENTIFIER_STRING) != std::string::npos) && (iter->find(ADAPTER_RAM_IDENTIFIER_STRING) == 0))
            {
				std::string capacityString = iter->substr(iter->find(ADAPTER_RAM_IDENTIFIER_STRING) + std::strlen(ADAPTER_RAM_IDENTIFIER_STRING));
				long long int capacity{ 0 };
				try
                {
					capacity = std::stoll(capacityString);
					GPUInfo.AdapterRAM = std::to_string(capacity / 1000000) + "MB (" + std::to_string(capacity) + " Bytes)";
				}
				catch (std::exception& e)
                {
					(void)e;
					GPUInfo.AdapterRAM = capacityString + " Bytes";
				}
			}

			if (FIND_IN_ITER(REFRESH_RATE_IDENTIFIER_STRING)) {
			// Refresh Rate
				GPUInfo.RefreshRate = iter->substr(iter->find(REFRESH_RATE_IDENTIFIER_STRING) + std::strlen(REFRESH_RATE_IDENTIFIER_STRING)) + "MHz";
				if (GPUInfo.RefreshRate == "MHz") {
					GPUInfo.RefreshRate = "";
				}
			}

			// Driver Version
			if (FIND_IN_ITER(DRIVER_VERSION_IDENTIFIER_STRING))
				GPUInfo.DriverVersion = iter->substr(iter->find(DRIVER_VERSION_IDENTIFIER_STRING) + std::strlen(DRIVER_VERSION_IDENTIFIER_STRING));

			// Video Architecture
			if (FIND_IN_ITER(VIDEO_ARCHITECTURE_IDENTIFIER_STRING))
				GPUInfo.VideoArchitecture = DetermineVideoArchitecture(iter->substr(iter->find(VIDEO_ARCHITECTURE_IDENTIFIER_STRING), std::strlen(VIDEO_ARCHITECTURE_IDENTIFIER_STRING)));

			// Video Memory Type
			if (FIND_IN_ITER(VIDEO_MEMORY_TYPE_IDENTIFIER_STRING))
				GPUInfo.VideoMemoryType = DetermineVideoMemoryType(iter->substr(iter->find(VIDEO_MEMORY_TYPE_IDENTIFIER_STRING), std::strlen(VIDEO_MEMORY_TYPE_IDENTIFIER_STRING)));

			// Video Mode Description
			if (FIND_IN_ITER(VIDEO_MODE_DESCRIPTION_IDENTIFIER_STRING))
				GPUInfo.VideoModeDescription = iter->substr(iter->find(VIDEO_MODE_DESCRIPTION_IDENTIFIER_STRING) + std::strlen(VIDEO_MODE_DESCRIPTION_IDENTIFIER_STRING));

			// Video Processor
			if (FIND_IN_ITER(VIDEO_PROCESSOR_IDENTIFIER_STRING))
				GPUInfo.VideoProcessor = iter->substr(iter->find(VIDEO_PROCESSOR_IDENTIFIER_STRING) + std::strlen(VIDEO_PROCESSOR_IDENTIFIER_STRING));
		}

		GPUsInfo.push_back(GPUInfo);
	}
}

const char* FGPUInfoCollector::DetermineVideoArchitecture(const std::string videoArchitectureStr) const
{
    int videoArchitecture = 2;
    
    try {
        videoArchitecture = std::stoi(videoArchitectureStr);
    } catch (std::exception& e) {
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

const char* FGPUInfoCollector::DetermineVideoMemoryType(const std::string& videoMemoryTypeStr) const
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