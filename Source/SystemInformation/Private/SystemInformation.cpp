// Copyright Epic Games, Inc. All Rights Reserved.

#include "SystemInformation.h"

#include "JsonUtilities.h"
#include "JsonDomBuilder.h"
#include "ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/lib/Fuzzer/FuzzerInternal.h"

#define LOCTEXT_NAMESPACE "FSystemInformationModule"

TArray<FMotherboardInformation> FSystemInformation::m_MotherboardsInfo = {};
TArray<FOperatingSystemInformation> FSystemInformation::m_OperatingSystemsInfo = {};
TArray<FCPUInformation> FSystemInformation::m_CPUsInfo = {};
TArray<FGPUInformation> FSystemInformation::m_GPUsInfo = {};
TArray<FRAMInformation> FSystemInformation::m_RAMsInfo = {};
TArray<FHardDiskInformation> FSystemInformation::m_HardDisksInfo = {};

void FSystemInformation::WriteToJsonFile(FString FileName, bool bShouldRefetch /* = false */)
{
	if(bShouldRefetch)
	{
		FetchInfo();
	}
	
	FJsonDomBuilder::FObject object;

	// Motherboards
	for (auto it : m_MotherboardsInfo)
	{
		FString key = TEXT("Motherboard");
		key.AppendInt(it.Index);

		FString value;

		if (!FJsonObjectConverter::UStructToJsonObjectString(it, value, 0, 0, 0, nullptr, false))
			UE_LOG(LogTemp, Error, TEXT(""));

		object.Set(key, value);
	}

	// Operating systems
	for (auto it : m_OperatingSystemsInfo)
	{
		FString key = TEXT("OperatingSystem");
		key.AppendInt(it.Index);

		FString value;
		if (!FJsonObjectConverter::UStructToJsonObjectString(it, value, 0, 0, 0, nullptr, false))
			UE_LOG(LogTemp, Error, TEXT(""));

		object.Set(key, value);
	}

	// CPUs
	for (auto it : m_CPUsInfo)
	{
		FString key = TEXT("CPU");
		key.AppendInt(it.Index);

		FString value;
		if (!FJsonObjectConverter::UStructToJsonObjectString(it, value, 0, 0, 0, nullptr, false))
			UE_LOG(LogTemp, Error, TEXT(""));

		object.Set(key, value);
	}

	// GPUs
	for (auto it : m_GPUsInfo)
	{
		FString key = TEXT("GPU");
		key.AppendInt(it.Index);

		FString value;
		if (!FJsonObjectConverter::UStructToJsonObjectString(it, value, 0, 0, 0, nullptr, false))
			UE_LOG(LogTemp, Error, TEXT(""));

		object.Set(key, value);
	}

	// RAMs
	for (auto it : m_RAMsInfo)
	{
		FString key = TEXT("RAM");
		key.AppendInt(it.Index);

		FString value;
		if (!FJsonObjectConverter::UStructToJsonObjectString(it, value, 0, 0, 0, nullptr, false))
			UE_LOG(LogTemp, Error, TEXT(""));

		object.Set(key, value);
	}

	// Hard disks
	for (auto it : m_HardDisksInfo)
	{
		FString key = TEXT("HardDisk");
		key.AppendInt(it.Index);

		FString value;
		if (!FJsonObjectConverter::UStructToJsonObjectString(it, value, 0, 0, 0, nullptr, false))
			UE_LOG(LogTemp, Error, TEXT(""));

		object.Set(key, value);
	}

	// Convert to string
	FString jsonString = object.ToString<TCondensedJsonPrintPolicy>();
	jsonString = jsonString.Replace(TEXT("\\"), TEXT(""));
	jsonString = jsonString.Replace(TEXT("\"{"), TEXT("{"));
	jsonString = jsonString.Replace(TEXT("}\""), TEXT("}"));

	// Save to file
	FFileHelper::SaveStringToFile(jsonString, *(FPaths::ProjectSavedDir() + FileName));
}

void FSystemInformation::FetchInfo()
{
	m_MotherboardsInfo = FMotherboardInformationFetcher::FetchInfo();
	m_OperatingSystemsInfo = FOperatingSystemInformationFetcher::FetchInfo();
	m_CPUsInfo = FCPUInformationFetcher::FetchInfo();
	m_GPUsInfo = FGPUInformationFetcher::FetchInfo();
	m_RAMsInfo = FRAMInformationFetcher::FetchInfo();
	m_HardDisksInfo = FHardDiskInformationFetcher::FetchInfo();
}

void FSystemInformationModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FSystemInformation::FetchInfo();
	FSystemInformation::WriteToJsonFile("SystemInformation.json");
}

void FSystemInformationModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSystemInformationModule, SystemInformation)