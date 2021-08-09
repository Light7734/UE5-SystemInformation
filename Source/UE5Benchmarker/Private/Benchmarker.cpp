// Fill out your copyright notice in the Description page of Project Settings.

#include "Benchmarker.h"

ABenchmarker* ABenchmarker::StaticInstance = nullptr;

ABenchmarker::ABenchmarker()
{
	StaticInstance = this;

	FStatsThreadState& Stats = FStatsThreadState::GetLocalState();

	// This is the name of the group where stats are.
	FName GroupName = FName(TEXT("STAT_Platform"));

	TArray<FName> GroupItems;
	Stats.Groups.MultiFind(GroupName, GroupItems);

	// Prepare the set of names and raw names of the stats we want to get
	for (const FName& ShortName : GroupItems)
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *ShortName.ToString());
		StatsFilter.AddItem(ShortName);
		if (FStatMessage const* LongName = Stats.ShortNameToLongName.Find(ShortName))
		{
			StatsFilter.AddItem(LongName->NameAndInfo.GetRawName());
		}
	}
}

void ABenchmarker::Tick(float DeltaSeconds)
{
	FPS = 1.0f / DeltaSeconds;
	AvgFPS = AvgFPS + ((FPS - AvgFPS) / ++TotalFrames);
}

void ABenchmarker::BeginPlay()
{
	Super::BeginPlay();

	FStatsThreadState& Stats = FStatsThreadState::GetLocalState();
	StatsMasterEnableAdd();

	DelegateHandle = Stats.NewFrameDelegate.AddStatic(&DumpCPU);
	if (DelegateHandle.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Added TestBenchmarkHUD Stats.NewFrameDelegate"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to add TestBenchmarkHUD Stats.NewFrameDelegate"));
	}
}

void ABenchmarker::BeginDestroy()
{
	Super::BeginDestroy();

	FStatsThreadState& Stats = FStatsThreadState::GetLocalState();

	if (Stats.NewFrameDelegate.Remove(StaticInstance->DelegateHandle))
	{
		UE_LOG(LogTemp, Log, TEXT("Removed TestBenchmarkHUD Stats.NewFrameDelegate"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to remove TestBenchmarkHUD Stats.NewFrameDelegate"));
	}

	StatsMasterEnableSubtract();
}

void ABenchmarker::DumpCPU(int64 Frame) // static
{
	UE_LOG(LogTemp, Log, TEXT("ABenchmarker::DumpCPU: AA"));
	if (!StaticInstance)
	{
		UE_LOG(LogTemp, Log, TEXT("ABenchmarker::DumpCPU: StaticInstance is invalid"));
		return;
	}

	FStatsThreadState& Stats = FStatsThreadState::GetLocalState();

	if (!Stats.IsFrameValid(Frame))
	{
		UE_LOG(LogTemp, Log, TEXT("ABenchmarker::DumpCPU: Frame is invalid"));
		return;
	}

	// Create empty stat stack node (needed by stats gathering function)
	FRawStatStackNode HierarchyInclusive;

	// Prepare the array for stat messages
	TArray<FStatMessage> NonStackStats;

	// COLLECT ALL STATS TO THE ARRAY HERE
	Stats.UncondenseStackStats(Frame, HierarchyInclusive, &StaticInstance->StatsFilter, &NonStackStats);

	// Go through all stats
	unsigned int statCount = 0u;
	for (auto Stat : NonStackStats)
	{
		statCount++;
		// Here we are getting the raw name
		FName StatName = Stat.NameAndInfo.GetShortName();
		FString StatNameString = StatName.GetPlainNameString();

		// Here we are getting values
		int64 iVal = 0;
		double dVal = 0;
		switch (Stat.NameAndInfo.GetField<EStatDataType>())
		{
		case EStatDataType::ST_int64:
			iVal = Stat.GetValue_int64();
			UE_LOG(LogTemp, Log, TEXT("%s: %lld"), *StatName.ToString(), iVal);
			break;

		case EStatDataType::ST_double:
			dVal = Stat.GetValue_double();
			UE_LOG(LogTemp, Log, TEXT("%s: %f"), dVal);
			break;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Received Stat: %u"), statCount);
}