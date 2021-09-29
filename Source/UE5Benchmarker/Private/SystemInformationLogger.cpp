// Created by Light3039, under MIT5 license

#include "SystemInformationLogger.h"

#include "InfoMotherboard.h"
#include "InfoOS.h"
#include "InfoRam.h"
#include "InfoCPU.h"
#include "InfoGPU.h"
#include "InfoHardDisk.h"

ASystemInformationLogger::ASystemInformationLogger()
{
	for (const auto& motherboardInfo : HardwareInfo::FMotherboard::FetchInfo())
		motherboardInfo.LogToUE_LOG();

	for (const auto& osInfo : HardwareInfo::FOperatingSystem::FetchInfo())
		osInfo.LogToUE_LOG();

	for (const auto& cpuInfo : HardwareInfo::FCPU::FetchInfo())
		cpuInfo.LogToUE_LOG();

	for (const auto& gpuInfo : HardwareInfo::FGPU::FetchInfo())
		gpuInfo.LogToUE_LOG();

	for (const auto& ramInfo : HardwareInfo::FRAM::FetchInfo())
		ramInfo.LogToUE_LOG();

	for (const auto& hardDiskinfo : HardwareInfo::FHardDisk::FetchInfo())
		hardDiskinfo.LogToUE_LOG();
}