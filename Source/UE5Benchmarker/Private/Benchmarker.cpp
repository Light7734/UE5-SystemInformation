// Fill out your copyright notice in the Description page of Project Settings.


#include "Benchmarker.h"

ABenchmarker* ABenchmarker::StaticInstance = nullptr;

ABenchmarker::ABenchmarker()
{
	StaticInstance = this;

	SetActorTickEnabled(true);

	FStatsThreadState& Stats = FStatsThreadState::GetLocalState();

	// This is the name of the group where stats are.
	// #todo: use specific stats instead of the stat groups if possible
	FName GroupNames[]
	{
		TEXT("STATGROUP_RHI"),
		TEXT("STATGROUP_LightRendering")
	};
	StatsFilter.AddItem("STAT_FrameTime");

	for (FName GroupName : GroupNames)
	{
		TArray<FName> GroupItems;
		Stats.Groups.MultiFind(GroupName, GroupItems);

		// Prepare the set of names and raw names of the stats we want to get
		for (const FName& ShortName : GroupItems)
		{
			if (FStatMessage const* LongName = Stats.ShortNameToLongName.Find(ShortName))
			{
				FName rawName = LongName->NameAndInfo.GetRawName();
				UE_LOG(LogTemp, Log, TEXT("%s"), *rawName.ToString());
				StatsFilter.AddItem(rawName);
			}
			else 
				UE_LOG(LogTemp, Log, TEXT("This, this is all wrong"));
		}
	}
}

void ABenchmarker::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AvgDeltaSeconds += (DeltaSeconds - AvgDeltaSeconds) / ++TotalTicks;
}

void ABenchmarker::BeginPlay()
{
	// I have no idea why but if I don't put these here, it doesn't work
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;

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

	avgFrameStats.avgDeltaSeconds = AvgDeltaSeconds;
	avgFrameStats.totalTicks = TotalTicks;

	avgFrameStats.DumpToLog();

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
	static bool openFile = false;

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

	FrameStats frameStats;

	// Create empty stat stack node (needed by stats gathering function)
	FRawStatStackNode HierarchyInclusive;

	// Prepare the array for stat messages
	TArray<FStatMessage> NonStackStats;

	// COLLECT ALL STATS TO THE ARRAY HERE
	Stats.UncondenseStackStats(Frame, HierarchyInclusive, &StaticInstance->StatsFilter, &NonStackStats);

	// Go through all stats
	unsigned int statCount = 0u;

	auto& avgFrameStats = StaticInstance->avgFrameStats;
	avgFrameStats.totalDumps++;

	for (auto Stat : NonStackStats)
	{
		statCount++;
		FName StatName = Stat.NameAndInfo.GetRawName();
		FString StatNameStr = *StatName.ToString();
		
		static bool test = false;

		switch (HashStr(TCHAR_TO_ANSI(*StatNameStr + 12)))
		{
		case HashStr("RHI"):
			switch (HashStr(TCHAR_TO_ANSI(*StatNameStr + 22)))
			{
			case HashStr("RHITriangles"):
				avgFrameStats.nTriangles += (Stat.GetValue_int64() - avgFrameStats.nTriangles) / (double)avgFrameStats.totalDumps;
				break;
			case HashStr("RHIDrawPrimitiveCalls"):
				avgFrameStats.nDrawPrimitiveCalls += (Stat.GetValue_int64() - avgFrameStats.nDrawPrimitiveCalls) / (double)avgFrameStats.totalDumps;
				break;
			}
			break;
		}
	}
}