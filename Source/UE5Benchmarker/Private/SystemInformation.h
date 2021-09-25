// Created by Light3039, under MIT5 license

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemInformation.generated.h"

struct FCPUInformation
{

};

UCLASS()
class ASystemInformation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASystemInformation();

	void FetchCPUInformation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FCPUInformation CPUInformation;
};
