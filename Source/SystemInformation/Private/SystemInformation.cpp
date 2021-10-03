// Copyright Epic Games, Inc. All Rights Reserved.

#include "SystemInformation.h"

#define LOCTEXT_NAMESPACE "FSystemInformationModule"

TArray<SystemInfo::FMotherboard::Info> FSystemInformation::m_MotherboardsInfo = {};
TArray<SystemInfo::FOperatingSystem::Info> FSystemInformation::m_OperatingSystemsInfo = {};
TArray<SystemInfo::FCPU::Info> FSystemInformation::m_CPUsInfo = {};
TArray<SystemInfo::FGPU::Info> FSystemInformation::m_GPUsInfo = {};
TArray<SystemInfo::FRAM::Info> FSystemInformation::m_RAMsInfo = {};
TArray<SystemInfo::FHardDisk::Info> FSystemInformation::m_HardDisksInfo = {};

void FSystemInformation::FetchInfo()
{
	m_MotherboardsInfo = SystemInfo::FMotherboard::FetchInfo();
	m_OperatingSystemsInfo = SystemInfo::FOperatingSystem::FetchInfo();
	m_CPUsInfo = SystemInfo::FCPU::FetchInfo();
	m_GPUsInfo = SystemInfo::FGPU::FetchInfo();
	m_RAMsInfo = SystemInfo::FRAM::FetchInfo();
	m_HardDisksInfo = SystemInfo::FHardDisk::FetchInfo();
}

void FSystemInformationModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FSystemInformation::FetchInfo();
}

void FSystemInformationModule::ShutdownModule()
{
	
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSystemInformationModule, SystemInformation)
