// Created by Light3039, under MIT5 license

#include "SystemInformation.h"

#include <intrin.h>

#include "cpuinfodelegate.h"
#include "gpuinfodelegate.h"
#include "motherboardinfodelegate.h"
#include "raminfo.h"
#include "osinfodelegate.h"

// Sets default values
ASystemInformation::ASystemInformation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//First make a delegate object that handles the cases where the computer has multiple CPUs
	std::unique_ptr<CPUInfoDelegate> cpuInfo = std::make_unique<CPUInfoDelegate>();

	//Then extract the separate CPUs into a vector (of CPUInfo objects)
	std::vector<CPUInfo> cpuInfoVector{ cpuInfo->cpuInfoVector() };

	//Print out the number of CPUs, directory from the delegate object
	for (std::vector<CPUInfo>::const_iterator iter = cpuInfoVector.begin(); iter != cpuInfoVector.end(); iter++)
	{
		UE_LOG(LogTemp, Log, TEXT("Information for CPU #%i"), iter->cpuNumber() + 1);
		UE_LOG(LogTemp, Log, TEXT("CPU Name = %s"), *FString(iter->name().c_str()));
		UE_LOG(LogTemp, Log, TEXT("CPU Manufacturer = %s"), *FString(iter->manufacturer().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Number of CPU Cores = %s"), *FString(iter->numberOfCores().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Current CPU Clock Speed = %s"), *FString(iter->currentClockSpeed().c_str()));
		UE_LOG(LogTemp, Log, TEXT("CPU Architecture = %s"), *FString(iter->architecture().c_str()));
		UE_LOG(LogTemp, Log, TEXT("CPU L2 Cache Size = %s"), *FString(iter->L2CacheSize().c_str()));
		UE_LOG(LogTemp, Log, TEXT("CPU L3 Cache Size = %s"), *FString(iter->L3CacheSize().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Current CPU Temperature = %s"), *FString(iter->currentTemperature().c_str()));
	}

	std::unique_ptr<MotherboardInfoDelegate> moboInfo = std::make_unique<MotherboardInfoDelegate>();
	std::vector<MotherboardInfo> moboInfoVector = moboInfo->motherboardInfoVector();
	UE_LOG(LogTemp, Log, TEXT("Motherboard(s) installed %i"), moboInfo->numberOfMotherboardInfoItems());

	for (std::vector<MotherboardInfo>::const_iterator iter = moboInfoVector.begin(); iter != moboInfoVector.end(); iter++)
	{
		UE_LOG(LogTemp, Log, TEXT("Information for motherboard #%i"), iter->motherboardNumber());
		UE_LOG(LogTemp, Log, TEXT("Motherboard Name = %s"), *FString(iter->name().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Motherboard Manufacturer = %s"), *FString(iter->manufacturer().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Motherboard Chipset = %s"), *FString(iter->chipset().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Motherboard Serial Number = %s"), *FString(iter->serialNumber().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Motherboard Version = %s"), *FString(iter->version().c_str()));
	}

	FRAMInformationGatherer RAMInformationGatherer;
	std::vector<FRAMInformation> RAMsInformation = RAMInformationGatherer.GetRAMsInformation();
	UE_LOG(LogTemp, Log, TEXT("RAM stick(s) installed %i"), RAMInformationGatherer.GetRAMCount());

	for (const auto& RAMInformation : RAMsInformation)
	{
		UE_LOG(LogTemp, Log, TEXT("Information for RAM stick #%i"), RAMInformation.Index);
		UE_LOG(LogTemp, Log, TEXT("RAM Name = %s"), *FString(RAMInformation.Name.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM Manufacturer = %s"), *FString(RAMInformation.Manufacturer.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM Capacity = %s"), *FString(RAMInformation.Capacity.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM Serial Number = %s"), *FString(RAMInformation.SerialNumber.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM Form Factor = %s"), *FString(RAMInformation.FormFactor.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM Part Number = %s"), *FString(RAMInformation.PartNumber.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM Memory Type = %s"), *FString(RAMInformation.MemoryType.c_str()));
		UE_LOG(LogTemp, Log, TEXT("RAM Clock Speed = %s"), *FString(RAMInformation.ClockSpeed.c_str()));
	}

	std::unique_ptr<GPUInfoDelegate> gpuInfo = std::make_unique<GPUInfoDelegate>();
	std::vector<GPUInfo> gpuInfoVector = gpuInfo->gpuInfoVector();
	UE_LOG(LogTemp, Log, TEXT("GPU(s) installed %i"), gpuInfo->numberOfGPUInfoItems());
	for (std::vector<GPUInfo>::const_iterator iter = gpuInfoVector.begin(); iter != gpuInfoVector.end(); iter++)
	{
		UE_LOG(LogTemp, Log, TEXT("Information for GPU #%i"), iter->gpuNumber());
		UE_LOG(LogTemp, Log, TEXT("GPU Name = %s"), *FString(iter->name().c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Manufacturer = %s"), *FString(iter->manufacturer().c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Caption = %s"), *FString(iter->caption().c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Adapter RAM = %s"), *FString(iter->adapterRAM().c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Refresh Rate = %s"), *FString(iter->refreshRate().c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Driver Version = %s"), *FString(iter->driverVersion().c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Video Architecture = %s"), *FString(iter->videoArchitecture().c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Video Mode Description = %s"), *FString(iter->videoModeDescription().c_str()));
		UE_LOG(LogTemp, Log, TEXT("GPU Video Processor = %s"), *FString(iter->videoProcessor().c_str()));
	}

	std::unique_ptr<OSInfoDelegate> osInfo = std::make_unique<OSInfoDelegate>();
	std::vector<OSInfo> osInfoVector = osInfo->osInfoVector();
	UE_LOG(LogTemp, Log, TEXT("OS(s) installed %i"), osInfo->numberOfOSInfoItems());
	for (std::vector<OSInfo>::const_iterator iter = osInfoVector.begin(); iter != osInfoVector.end(); iter++)
	{
		UE_LOG(LogTemp, Log, TEXT("Information for OS #%i"), iter->osNumber());
		UE_LOG(LogTemp, Log, TEXT("OS Name = %s"), *FString(iter->name().c_str()));
		UE_LOG(LogTemp, Log, TEXT("OS Manufacturer = %s"), *FString(iter->manufacturer().c_str()));
		UE_LOG(LogTemp, Log, TEXT("OS Caption = %s"), *FString(iter->caption().c_str()));
		UE_LOG(LogTemp, Log, TEXT("OS Version = %s"), *FString(iter->version().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Current User = %s"), *FString(iter->currentUser().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Install Date = %s"), *FString(iter->installDate().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Build Number = %s"), *FString(iter->buildNumber().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Last Boot Up Time = %s"), *FString(iter->lastBootUpTime().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Boot Device = %s"), *FString(iter->bootDevice().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Total Virtual Memory = %s"), *FString(iter->totalVirtualMemory().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Total Visible Memory = %s"), *FString(iter->totalVisibleMemory().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Total Swap Size = %s"), *FString(iter->totalSwapSize().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Serial Number = %s"), *FString(iter->serialNumber().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Free Physical Memory = %s"), *FString(iter->freePhysicalMemory().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Free Virtual Memory = %s"), *FString(iter->freeVirtualMemory().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Free Paging File Space = %s"), *FString(iter->freePagingFileSpace().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Used Paging File Space = %s"), *FString(iter->usedPagingFileSpace().c_str()));
		UE_LOG(LogTemp, Log, TEXT("Current Date Time = %s"), *FString(iter->currentDateTime().c_str()));
	}
}

// Called when the game starts or when spawned
void ASystemInformation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASystemInformation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASystemInformation::FetchCPUInformation()
{
	int cpuInfo[4];

	for (int a = 0; a < 4; a++)
	{
		__cpuid(cpuInfo, a);
		UE_LOG(LogTemp, Log, TEXT("The code %i gives: %i, %i, %i, %i"), cpuInfo[0], cpuInfo[1], cpuInfo[2], cpuInfo[3]);
	}
}