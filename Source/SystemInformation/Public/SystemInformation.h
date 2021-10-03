// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "InfoMotherboard.h"
#include "InfoOS.h"
#include "InfoCPU.h"
#include "InfoGPU.h"
#include "InfoRAM.h"
#include "InfoHardDisk.h"

class SYSTEMINFORMATION_API FSystemInformation
{
private:
	friend class FSystemInformationModule;

public:
	FSystemInformation() = delete;

	static inline const TArray<SystemInfo::FMotherboard::Info>& GetMotherboardsInfo() { return m_MotherboardsInfo; }
	static inline const TArray<SystemInfo::FOperatingSystem::Info>& GetOperatingSystemsInfo() { return m_OperatingSystemsInfo; }
	static inline const TArray<SystemInfo::FCPU::Info>& GetCPUsInfo() { return m_CPUsInfo; }
	static inline const TArray<SystemInfo::FGPU::Info>& GetGPUsInfo() { return m_GPUsInfo; }
	static inline const TArray<SystemInfo::FRAM::Info>& GetRAMsInfo() { return m_RAMsInfo; }
	static inline const TArray<SystemInfo::FHardDisk::Info>& GetHardDisksInfo() { return m_HardDisksInfo; }

private:
	static void FetchInfo();

private:
	static TArray<SystemInfo::FMotherboard::Info> m_MotherboardsInfo;
	static TArray<SystemInfo::FOperatingSystem::Info> m_OperatingSystemsInfo;
	static TArray<SystemInfo::FCPU::Info> m_CPUsInfo;
	static TArray<SystemInfo::FGPU::Info> m_GPUsInfo;
	static TArray<SystemInfo::FRAM::Info> m_RAMsInfo;
	static TArray<SystemInfo::FHardDisk::Info> m_HardDisksInfo;
};

class FSystemInformationModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
