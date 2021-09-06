// #todo: comment stuff

#include "Benchmarker.h"

ABenchmarker* ABenchmarker::StaticInstance = nullptr;

ABenchmarker::ABenchmarker()
{
	StaticInstance = this;
	SetActorTickEnabled(true);

	FName GroupNames[]
	{
		TEXT("STATGROUP_RHI"),
		TEXT("STATGROUP_LightRendering")
	};
	StatsFilter.AddItem("STAT_FrameTime");

	FStatsThreadState& Stats = FStatsThreadState::GetLocalState();
	for (FName GroupName : GroupNames)
	{
		TArray<FName> StatGroup;
		Stats.Groups.MultiFind(GroupName, StatGroup);

		for (const FName& Stat : StatGroup)
		{
			TArray<FName> GroupFilter
			{
				TEXT("STAT_RHITriangles"),
				TEXT("STAT_RHIDrawPrimitiveCalls"),

				TEXT("STAT_NumReflectiveShadowMapLights"),
				TEXT("STAT_NumLightsUsingStandardDeferred"),
				TEXT("STAT_NumLightsUsingSimpleTiledDeferred"),
				TEXT("STAT_NumLightsUsingTiledDeferred"),
				TEXT("STAT_NumLightsInjectedIntoTranslucency"),
				TEXT("STAT_NumUnshadowedLights"),
				TEXT("STAT_NumLightFunctionOnlyLights"),
				TEXT("STAT_NumShadowedLights"),
				TEXT("STAT_LightRendering"),
				TEXT("STAT_DirectLightRenderingTime"),
				TEXT("STAT_TranslucentInjectTime"),
			};

			int32 index = GroupFilter.Find(*Stat.ToString());
			if (index != INDEX_NONE)
			{
				FStatMessage const* LongName = Stats.ShortNameToLongName.Find(Stat);
				if (LongName)
				{
					FName rawName = LongName->NameAndInfo.GetRawName();
					UE_LOG(LogTemp, Log, TEXT("Added [%s] to the stats filter (hash:%u)"), *Stat.ToString(), HashStrToNextSlash(TCHAR_TO_UTF8(*Stat.ToString())));
					StatsFilter.AddItem(rawName);
				}
				else
					UE_LOG(LogTemp, Log, TEXT("Failed to add [%s] to the stats filter!"), *Stat.ToString());
			}
			else
				UE_LOG(LogTemp, Log, TEXT("Skipped: %s"), *Stat.ToString());
		}
	}
}

void ABenchmarker::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	BenchmarkResults.DeltaSeconds.SubmitStatValue(DeltaSeconds);
	BenchmarkResults.TotalGameTicks++;
}

void ABenchmarker::BeginPlay()
{
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

	if (Stats.NewFrameDelegate.Remove(DelegateHandle))
	{
		UE_LOG(LogTemp, Log, TEXT("Removed TestBenchmarkHUD Stats.NewFrameDelegate"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to remove TestBenchmarkHUD Stats.NewFrameDelegate"));
	}
	StatsMasterEnableSubtract();

	BenchmarkResults.DumpToLog();
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

	FRawStatStackNode HierarchyInclusive;

	TArray<FStatMessage> NonStackStats;

	Stats.UncondenseStackStats(Frame, HierarchyInclusive, &StaticInstance->StatsFilter, &NonStackStats);

	unsigned int statCount = 0u;

	auto& BenchmarkResults = StaticInstance->BenchmarkResults;
	BenchmarkResults.TotalStatDumps++;
\
	for (auto Stat : NonStackStats)
	{
		statCount++;
		FName StatName = Stat.NameAndInfo.GetRawName();
		FString StatNameStr = *StatName.ToString();

		switch (HashStrToNextSlash(TCHAR_TO_ANSI(*StatNameStr + 12)))
		{
		case HashStr("RHI"):
			switch (HashStrToNextSlash(TCHAR_TO_ANSI(*StatNameStr + 22)))
			{
			case HashStr("RHITriangles"):
				BenchmarkResults.Triangles.SubmitStatMessage(Stat);
				break;
			case HashStr("RHIDrawPrimitiveCalls"):
				BenchmarkResults.DrawPrimitiveCalls.SubmitStatMessage(Stat);
				break;

			default:
				UE_LOG(LogTemp, Log, TEXT("Unhandled RHI stat: %s"), *Stat.NameAndInfo.GetShortName().ToString());
			}
			break;
		case HashStr("LightRendering"):
			switch (HashStrToNextSlash(TCHAR_TO_ANSI(*StatNameStr + 33)))
			{
			case HashStr("NumShadowedLights"):
				BenchmarkResults.ShadowedLights.SubmitStatMessage(Stat);
				break;

			case HashStr("NumLightsInjectedIntoTranslucency"):
				BenchmarkResults.LightsInjectedIntoTranslucency.SubmitStatMessage(Stat);
				break;

			case HashStr("NumLightsUsingStandardDeferred"):
				BenchmarkResults.LightsUsingStandardDeferred.SubmitStatMessage(Stat);
				break;

			default:
				UE_LOG(LogTemp, Log, TEXT("Unhandled LightRendering stat: %s"), *Stat.NameAndInfo.GetShortName().ToString());
			}
			break;

		default:
			UE_LOG(LogTemp, Log, TEXT("Unhandled [unknown group] stat: %s"), *Stat.NameAndInfo.GetShortName().ToString());
		}
	}
}