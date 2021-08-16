// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Stats/StatsData.h"

#include "Engine/Classes/Engine/Light.h"

#include <inttypes.h>

#include "Benchmarker.generated.h"

struct FrameStats
{
	double nActiveLights = 0.0;
	double nTriangles = 0.0;
	double nVertices = 0.0;
	double nDrawPrimitiveCalls = 0.0;

	double totalDumps = 0.0f;
	double totalTicks = 0.0f;

	double avgDeltaSeconds = 0.0f;

	double score = 0.0;

	// #todo: add CPU/GPU score multiplier
	void DumpToLog()
	{
		UE_LOG(LogTemp, Log, TEXT("___________________________________________________"));
		UE_LOG(LogTemp, Log, TEXT("Average nActiveLights: %f") , nActiveLights);
		UE_LOG(LogTemp, Log, TEXT("Average nTriangles: %f") , nTriangles);
		UE_LOG(LogTemp, Log, TEXT("Average nVertices: %f") , nVertices);
		UE_LOG(LogTemp, Log, TEXT("Average nDrawPrimitiveCalls: %f") , nDrawPrimitiveCalls);
		UE_LOG(LogTemp, Log, TEXT("------------------"));
		UE_LOG(LogTemp, Log, TEXT("Average FPS: %f") , 1.0 / avgDeltaSeconds);
		UE_LOG(LogTemp, Log, TEXT("Total stat dumps: %f"), totalTicks);
		UE_LOG(LogTemp, Log, TEXT("Total game ticks: %f"), totalTicks);
		// #todo: use a proper algorithm
		UE_LOG(LogTemp, Log, TEXT("Final Score: %f") , (nActiveLights + nTriangles + nVertices + nDrawPrimitiveCalls) * (1.0f / avgDeltaSeconds / 60.0f));
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
	unsigned int TotalFrames = 0u;
	FDelegateHandle DelegateHandle;

	static ABenchmarker* StaticInstance;

	FStatsFilter StatsFilter;

	FrameStats avgFrameStats;

	float AvgDeltaSeconds = 0.0f;
	unsigned int TotalTicks = 0u;

protected:
	float HorizontalOffset = 300.0f;

public:
	ABenchmarker();

protected:
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:
	static void DumpCPU(int64 frame);

	static constexpr unsigned int HashStr(const char* str, int h = 0)
	{
		return !str[h] || str[h] == '/' ? 5381 : (HashStr(str, h + 1) * 33) ^ str[h];
	}

};
