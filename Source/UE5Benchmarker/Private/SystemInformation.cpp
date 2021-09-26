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
	LogMotherboardInfo();
	LogOSInfo();
	LogCPUsInfo();
	LogGPUsInfo();
	LogRAMsInfo();
}

void ASystemInformation::LogMotherboardInfo()
{
	FMotherboardInfoCollector motherboardInfoCollector;
	for (const auto& motherboardInfo : motherboardInfoCollector.GetMotherboardsInformation())
	{
		UE_LOG(LogTemp, Log, TEXT("Information for motherboard #%i"), motherboardInfo.Index);
		UE_LOG(LogTemp, Log, TEXT("Motherboard Name = %s"), *FString(motherboardInfo.Name.c_str()));
		UE_LOG(LogTemp, Log, TEXT("Motherboard Manufacturer = %s"), *FString(motherboardInfo.Manufacturer.c_str()));
		UE_LOG(LogTemp, Log, TEXT("Motherboard Chipset = %s"), *FString(motherboardInfo.Chipset.c_str()));
		UE_LOG(LogTemp, Log, TEXT("Motherboard Serial Number = %s"), *FString(motherboardInfo.SerialNumber.c_str()));
		UE_LOG(LogTemp, Log, TEXT("Motherboard Version = %s"), *FString(motherboardInfo.Version.c_str()));
	}
}

void ASystemInformation::LogOSInfo()
{
	for (const auto& osInfo : HardwareInfo::FOS::FetchInfo())
		osInfo.LogToUE_LOG();
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

void ASystemInformation::LogGPUsInfo()
{
	FGPUInfoCollector GPUInfoCollector;
	for (const auto& GPUInfo : GPUInfoCollector.GetGPUsInformation())
	{
		UE_LOG(LogTemp, Log, TEXT("Information for GPU #%i"), GPUInfo.Index);
		UE_LOG(LogTemp, Log, TEXT("GPU Name = %s"), *FString(GPUInfo.Name.c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Manufacturer = %s"), *FString(GPUInfo.Manufacturer.c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Caption = %s"), *FString(GPUInfo.Caption.c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Adapter RAM = %s"), *FString(GPUInfo.AdapterRAM.c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Refresh Rate = %s"), *FString(GPUInfo.RefreshRate.c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Driver Version = %s"), *FString(GPUInfo.DriverVersion.c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Video Architecture = %s"), *FString(GPUInfo.VideoArchitecture.c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Video Mode Description = %s"), *FString(GPUInfo.VideoModeDescription.c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Video Processor = %s"), *FString(GPUInfo.VideoProcessor.c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Video Memory Type = %s"), *FString(GPUInfo.VideoMemoryType.c_str()));
	}
}

void ASystemInformation::LogRAMsInfo()
{
	for (const auto& RAMInformation : HardwareInfo::FRAM::FetchInfo())
	{
		UE_LOG(LogTemp, Log, TEXT("Information for RAM stick #%i"), RAMInformation.Index);
		UE_LOG(LogTemp, Log, TEXT("RAM Capacity = %s"), *FString(RAMInformation.Capacity.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM ConfiguredClockSpeed = %s"), *FString(RAMInformation.ConfiguredClockSpeed.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM ConfiguredVoltage = %s"), *FString(RAMInformation.ConfiguredVoltage.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM DataWidth = %s"), *FString(RAMInformation.DataWidth.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM DeviceLocator = %s"), *FString(RAMInformation.DeviceLocator.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM FormFactor = %s"), *FString(RAMInformation.FormFactor.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM InterleaveDataDepth = %s"), *FString(RAMInformation.InterleaveDataDepth.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM InterleavePosition = %s"), *FString(RAMInformation.InterleavePosition.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM Manufacturer = %s"), *FString(RAMInformation.Manufacturer.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM MaxVoltage = %s"), *FString(RAMInformation.MaxVoltage.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM MinVoltage = %s"), *FString(RAMInformation.MinVoltage.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM PartNumber = %s"), *FString(RAMInformation.PartNumber.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM SMBIOSMemoryType = %s"), *FString(RAMInformation.SMBIOSMemoryType.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM Speed = %s"), *FString(RAMInformation.Speed.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM Tag = %s"), *FString(RAMInformation.Tag.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM TotalWidth = %s"), *FString(RAMInformation.TotalWidth.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM TypeDetail = %s"), *FString(RAMInformation.TypeDetail.c_str()));
	}
}