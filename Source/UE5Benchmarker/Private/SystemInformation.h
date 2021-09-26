// Created by Light3039, under MIT5 license

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InfoMotherboard.h"
#include "InfoOS.h"
#include "InfoCPU.h"
#include "InfoGPU.h"
#include "InfoRAM.h"
// #include "InfoDisks.h"

#include "SystemInformation.generated.h"

UCLASS()
class ASystemInformation : public AActor
{
	GENERATED_BODY()
	
public:	
	ASystemInformation();

	void LogCPUsInfo();
	void LogGPUsInfo();
};
