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

	static inline const TArray<FMotherboardInformation>& GetMotherboardsInfo() { return m_MotherboardsInfo; }
	static inline const TArray<FOperatingSystemInformation>& GetOperatingSystemsInfo() { return m_OperatingSystemsInfo; }
	static inline const TArray<FCPUInformation>& GetCPUsInfo() { return m_CPUsInfo; }
	static inline const TArray<FGPUInformation>& GetGPUsInfo() { return m_GPUsInfo; }
	static inline const TArray<FRAMInformation>& GetRAMsInfo() { return m_RAMsInfo; }
	static inline const TArray<FHardDiskInformation>& GetHardDisksInfo() { return m_HardDisksInfo; }

private:
	static void FetchInfo();

private:
	static TArray<FMotherboardInformation> m_MotherboardsInfo;
	static TArray<FOperatingSystemInformation> m_OperatingSystemsInfo;
	static TArray<FCPUInformation> m_CPUsInfo;
	static TArray<FGPUInformation> m_GPUsInfo;
	static TArray<FRAMInformation> m_RAMsInfo;
	static TArray<FHardDiskInformation> m_HardDisksInfo;
};

class FSystemInformationModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
