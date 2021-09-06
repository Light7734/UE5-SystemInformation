#pragma once

#include "CoreMinimal.h"

#include "Stats/StatsData.h"

#include "Engine/Classes/Engine/Light.h"

#include "Benchmarker.generated.h"

struct FBenchmarkStat
{

	float AvgValue = 0.0f;
	float MaxValue = FLT_MIN;
	float MinValue = FLT_MAX;

	float SubmitCounter = 0.0f;

	inline void SubmitStatMessage(FStatMessage message) 
	{ 
		float value;

		switch(message.NameAndInfo.GetField<EStatDataType>())
		{
		case EStatDataType::ST_int64:
			value = (float)message.GetValue_int64();
			break;

		case EStatDataType::ST_double:
			value = (float)message.GetValue_double();
			break;

		default:
			UE_LOG(LogTemp, Log, TEXT("Invalid stat data type: %i "), (int32)message.NameAndInfo.GetField<EStatDataType>());
			return;
		}

		SubmitStatValue(value);
	}

	inline void SubmitStatValue(float value)
	{
		AvgValue += (value - AvgValue) / ++SubmitCounter;

		MaxValue = MaxValue > value ? MaxValue : value;
		MinValue = MinValue < value ? MinValue : value;
	}
};

struct FBenchmarkResults
{
	FBenchmarkStat ShadowedLights;
	FBenchmarkStat LightsInjectedIntoTranslucency;
	FBenchmarkStat LightsUsingStandardDeferred;
	FBenchmarkStat ActiveLights;

	FBenchmarkStat Triangles;
	FBenchmarkStat DrawPrimitiveCalls;

	FBenchmarkStat DeltaSeconds;

	uint64_t TotalStatDumps;
	uint64_t TotalGameTicks;

	float CPUScoreMultiplier = 0.0f; // :#todo
	float GPUScoreMultiplier = 0.0f; // :#todo

	float FinalScore = 69.420f; // noice

	void CalculateFinalScore()
	{
		// #todo: add some algorithm
	}

	void DumpToLog()
	{
		UE_LOG(LogTemp, Log, TEXT("___________________________________________________"));

		// LightRendering
		UE_LOG(LogTemp, Log, TEXT("Average ShadowedLights: %f [%f]"), ShadowedLights.AvgValue, ShadowedLights.SubmitCounter);
		UE_LOG(LogTemp, Log, TEXT("Average LightsInjectedIntoTranslucency: %f [%f]"), LightsInjectedIntoTranslucency.AvgValue, LightsInjectedIntoTranslucency.SubmitCounter);
		UE_LOG(LogTemp, Log, TEXT("Average LightsUsingStandardDeferred: %f [%f]"), LightsUsingStandardDeferred.AvgValue, LightsUsingStandardDeferred.SubmitCounter);

		// RHI
		UE_LOG(LogTemp, Log, TEXT("Average Triangles: %f [%f]") , Triangles.AvgValue, Triangles.SubmitCounter);
		UE_LOG(LogTemp, Log, TEXT("Average DrawPrimitiveCalls: %f [%f]") , DrawPrimitiveCalls.AvgValue, DrawPrimitiveCalls.SubmitCounter);

		UE_LOG(LogTemp, Log, TEXT("------------------"));
		UE_LOG(LogTemp, Log, TEXT("Average FPS: %f [%f]"), 1.0f / DeltaSeconds.AvgValue, DeltaSeconds.SubmitCounter);

		UE_LOG(LogTemp, Log, TEXT("Total stat dumps: %llu"), TotalStatDumps);
		UE_LOG(LogTemp, Log, TEXT("Total game ticks: %llu"), TotalGameTicks);

		UE_LOG(LogTemp, Log, TEXT("Final Score: %f") , FinalScore);
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

	static constexpr unsigned int HashStr(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (HashStr(str, h + 1) * 33) ^ str[h];
	}

	static unsigned int HashStrToNextSlash(const char* str, int h = 0)
	{
		return str[h] == '/' ? 5381 : (HashStrToNextSlash(str, h + 1) * 33) ^ str[h];
	}
};