// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Stats/StatsData.h"

#include "Engine/Classes/Engine/Light.h"

#include "Benchmarker.generated.h"

struct FrameStats
{
	unsigned int nActiveLights;
	unsigned int nTriangles;
	unsigned int nVertices;

	float deltaTime;
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
	FDelegateHandle DelegateHandle;

	float FPS = 0.0f;
	float AvgFPS = 0.0f;
	unsigned int TotalFrames = 0u;

	static ABenchmarker* StaticInstance;

	FStatsFilter StatsFilter;

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
};
