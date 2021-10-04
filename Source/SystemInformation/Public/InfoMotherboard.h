#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

#include "InfoMotherboard.generated.h"

USTRUCT()
struct SYSTEMINFORMATION_API FMotherboardInformation
{
	GENERATED_BODY()

	UPROPERTY()
	FString Manufacturer = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Product = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Status = INFO_STR_UNKNOWN;

	UPROPERTY()
	FString Version = INFO_STR_UNKNOWN;

	UPROPERTY()
	uint8 Index = 0u;

	void LogToUE_LOG() const;
};


class SYSTEMINFORMATION_API FMotherboardInformationFetcher
{
public:
	static TArray<FMotherboardInformation> FetchInfo();

private:
	static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);
};

