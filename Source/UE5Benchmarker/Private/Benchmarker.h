#pragma once

#include "CoreMinimal.h"

#include "Stats/StatsData.h"

#include "Engine/Classes/Engine/Light.h"

#include "Benchmarker.generated.h"

struct FBenchmarkStat
{
	double avgValue = 0.0;
	double dumpCount = 0.0;

	inline void SubmitDump(double value) { avgValue += (value - avgValue) / ++dumpCount; }
};

struct FBenchmarkResults
{
	FBenchmarkStat nShadowedLights;
	FBenchmarkStat nLightsInjectedIntoTranslucency;
	FBenchmarkStat nLightsUsingStandardDeferred;
	FBenchmarkStat nActiveLights;

	FBenchmarkStat nTriangles;
	FBenchmarkStat nDrawPrimitiveCalls;

	FBenchmarkStat deltaSeconds;

	uint64_t totalDumps;
	uint64_t totalTicks;

	double cpuScoreMultiplier = 0.0; // :#todo
	double gpuScoreMultiplier = 0.0; // :#todo

	double finalScore = 69.420; // noice

	void CalculateFinalScore()
	{
		// #todo: add some algorithm
	}

	void DumpToLog()
	{
		UE_LOG(LogTemp, Log, TEXT("___________________________________________________"));
		UE_LOG(LogTemp, Log, TEXT("Average nShadowedLights: %f [%f]"), nShadowedLights.avgValue, nShadowedLights.dumpCount);
		UE_LOG(LogTemp, Log, TEXT("Average nLightsInjectedIntoTranslucency: %f [%f]"), nLightsInjectedIntoTranslucency.avgValue, nLightsInjectedIntoTranslucency.dumpCount);
		UE_LOG(LogTemp, Log, TEXT("Average nLightsUsingStandardDeferred: %f [%f]"), nLightsUsingStandardDeferred.avgValue, nLightsUsingStandardDeferred.dumpCount);
		UE_LOG(LogTemp, Log, TEXT("Average nTriangles: %f [%f]") , nTriangles.avgValue, nTriangles.dumpCount);
		UE_LOG(LogTemp, Log, TEXT("Average nDrawPrimitiveCalls: %f [%f]") , nDrawPrimitiveCalls.avgValue, nDrawPrimitiveCalls.dumpCount);

		UE_LOG(LogTemp, Log, TEXT("------------------"));
		UE_LOG(LogTemp, Log, TEXT("Average FPS: %f [%f]"), 1.0f / deltaSeconds.avgValue, deltaSeconds.dumpCount);
		UE_LOG(LogTemp, Log, TEXT("Total stat dumps: %llu"), totalDumps);
		UE_LOG(LogTemp, Log, TEXT("Total game ticks: %llu"), totalTicks);

		UE_LOG(LogTemp, Log, TEXT("Final Score: %f") , finalScore);
		UE_LOG(LogTemp, Log, TEXT("___________________________________________________"));
	}
};

struct FStatsFilter : public IItemFilter
{
	TSet<FName> EnabledItems;

	inline void AddItem(const FName& InElement)
	{
		EnabledItems.Add(InElement);
	}

	virtual bool Keep(FStatMessage const& Item)
	{
		const FName MessageName = Item.NameAndInfo.GetRawName();
		return EnabledItems.Contains(MessageName);
	}
};

UCLASS(NotBlueprintable)
class ABenchmarker : public AActor
{
	GENERATED_BODY()

private:
	static ABenchmarker* StaticInstance;

	FBenchmarkResults BenchmarkResults;

	FDelegateHandle DelegateHandle;
	FStatsFilter StatsFilter;

public:
	ABenchmarker();

protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:
	static void DumpCPU(int64 frame);

	static unsigned int HashStrToNextSlash(const char* str, int h = 0)
	{
		return str[h] == '/' ? 5381 : (HashStrToNextSlash(str, h + 1) * 33) ^ str[h];
	}

	static constexpr unsigned int HashStr(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (HashStr(str, h + 1) * 33) ^ str[h];
	}

};
