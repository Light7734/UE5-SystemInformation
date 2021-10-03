#pragma once

#include "CoreMinimal.h"

#include "InfoBase.h"

namespace SystemInfo {

	class SYSTEMINFORMATION_API FMotherboard
	{
	public:
		struct SYSTEMINFORMATION_API Info
		{
			FString Manufacturer = INFO_STR_UNKNOWN;
			FString Product = INFO_STR_UNKNOWN;
			FString Status = INFO_STR_UNKNOWN;
			FString Version = INFO_STR_UNKNOWN;

			uint8_t Index = 0u;

			void LogToUE_LOG() const;
		};

	public:
		static TArray<Info> FetchInfo();

	private:
		static void TryFetchField(const FString& iter, const char* fieldName, FString& outValue);
	};

}