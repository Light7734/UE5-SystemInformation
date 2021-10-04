// Copyright Epic Games, Inc. All Rights Reserved.

#include "SystemInformation.h"

#include "JsonUtilities.h"
#include "JsonDomBuilder.h"

#define LOCTEXT_NAMESPACE "FSystemInformationModule"

TArray<FMotherboardInformation> FSystemInformation::m_MotherboardsInfo = {};
TArray<FOperatingSystemInformation> FSystemInformation::m_OperatingSystemsInfo = {};
TArray<FCPUInformation> FSystemInformation::m_CPUsInfo = {};
TArray<FGPUInformation> FSystemInformation::m_GPUsInfo = {};
TArray<FRAMInformation> FSystemInformation::m_RAMsInfo = {};
TArray<FHardDiskInformation> FSystemInformation::m_HardDisksInfo = {};

void FSystemInformation::FetchInfo()
{
	m_MotherboardsInfo = FMotherboardInformationFetcher::FetchInfo();
	m_OperatingSystemsInfo = FOperatingSystemInformationFetcher::FetchInfo();
	m_CPUsInfo = FCPUInformationFetcher::FetchInfo();
	m_GPUsInfo = FGPUInformationFetcher::FetchInfo();
	m_RAMsInfo = FRAMInformationFetcher::FetchInfo();
	m_HardDisksInfo = FHardDiskInformationFetcher::FetchInfo();

	for (auto it : m_MotherboardsInfo)
	{
 		FString motherboardJsonString;
		if (FJsonObjectConverter::UStructToJsonObjectString(it, motherboardJsonString))
			UE_LOG(LogTemp, Error, TEXT(""));
	}
	
	for (auto it : m_OperatingSystemsInfo)
	{
		FString operatingSystemJsonString;
		if (FJsonObjectConverter::UStructToJsonObjectString(it, operatingSystemJsonString))
			UE_LOG(LogTemp, Error, TEXT(""));
	}
	
	for (auto it : m_GPUsInfo)
	{
		FString gpuJsonString;
		if (FJsonObjectConverter::UStructToJsonObjectString(it, gpuJsonString))
			UE_LOG(LogTemp, Error, TEXT(""));
	}
	
	for (auto it : m_RAMsInfo)
	{
		FString ramJsonString;
		if (FJsonObjectConverter::UStructToJsonObjectString(it, ramJsonString))
			UE_LOG(LogTemp, Error, TEXT(""));
	}
	
	for (auto it : m_HardDisksInfo)
	{
		FString hardDiskJsonString;
	
		if (FJsonObjectConverter::UStructToJsonObjectString(it, hardDiskJsonString))
			UE_LOG(LogTemp, Error, TEXT(""));
	}

	// FJsonDomBuilder::FArray InnerArray;
	// InnerArray.Add(7.f, TEXT("Hello"), true);
	// 
	// FJsonDomBuilder::FObject Object;
	// Object.Set(TEXT("Array"), InnerArray);
	// Object.Set(TEXT("Number"), 13.f);
	// 
	// Object.AsJsonValue();
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