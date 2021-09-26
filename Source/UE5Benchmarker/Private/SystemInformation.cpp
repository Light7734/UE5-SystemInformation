// Created by Light3039, under MIT5 license

#include "SystemInformation.h"

#include <intrin.h>

#include "InfoMotherboard.h"
#include "InfoOS.h"
#include "InfoRam.h"
#include "InfoCPU.h"
#include "InfoGPU.h"

ASystemInformation::ASystemInformation()
{
	for (const auto& motherboardInfo : HardwareInfo::FMotherboard::FetchInfo())
		motherboardInfo.LogToUE_LOG();

	for (const auto& osInfo : HardwareInfo::FOperatingSystem::FetchInfo())
		osInfo.LogToUE_LOG();

	for (const auto& gpuInfo : HardwareInfo::FGPU::FetchInfo())
		gpuInfo.LogToUE_LOG();

	for (const auto& ramInfo : HardwareInfo::FRAM::FetchInfo())
		ramInfo.LogToUE_LOG();
}

void ASystemInformation::LogCPUsInfo()
{
	FCPUInfoCollector cpuInfoCollector;
	for (const auto& cpuInfo : cpuInfoCollector.GetCPUsInformation())
	{
		UE_LOG(LogTemp, Log, TEXT("Information for CPU #%i"), cpuInfo.Index);

		UE_LOG(LogTemp, Log, TEXT("CPU Name = %s"), *FString(cpuInfo.Name.c_str()));
		UE_LOG(LogTemp, Log, TEXT("CPU Manufacturer = %s"), *FString(cpuInfo.Manufacturer.c_str()));
		UE_LOG(LogTemp, Log, TEXT("CPU Architecture = %s"), *FString(cpuInfo.Architecture.c_str()));

		UE_LOG(LogTemp, Log, TEXT("CPU Core Count = %s"), *FString(cpuInfo.CoreCount.c_str()));
		UE_LOG(LogTemp, Log, TEXT("CPU L2 Cache Size = %s"), *FString(cpuInfo.L2CacheSize.c_str()));
		UE_LOG(LogTemp, Log, TEXT("CPU L3 Cache Size = %s"), *FString(cpuInfo.L3CacheSize.c_str()));
		// UE_LOG(LogTemp, Log, TEXT("Current CPU Clock Speed = %s"), *FString(cpuInfo.c.c_str()));
		// UE_LOG(LogTemp, Log, TEXT("Current CPU Temperature = %s"), *FString(cpuInfo.tem.c_str()));
	}
}