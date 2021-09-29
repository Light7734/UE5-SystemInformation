#pragma once

#include "InfoBase.h"

#include <vector>

namespace HardwareInfo {

	class SYSTEMINFORMATION_API FMotherboard
	{
	public:
		struct Info
		{
			std::string Manufacturer = INFO_STR_UNKNOWN;
			std::string Product = INFO_STR_UNKNOWN;
			std::string Status = INFO_STR_UNKNOWN;
			std::string Version = INFO_STR_UNKNOWN;

			uint8_t Index = 0u;

			void LogToUE_LOG() const
			{
				UE_LOG(LogTemp, Log, TEXT("Motherboard #%i {"), Index);
				UE_LOG(LogTemp, Log, TEXT("    Manufacturer = %s"), *FString(Manufacturer.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Product = %s"), *FString(Product.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Status = %s"), *FString(Status.c_str()));
				UE_LOG(LogTemp, Log, TEXT("    Version = %s"), *FString(Version.c_str()));
				UE_LOG(LogTemp, Log, TEXT("}"));
			}
		};

	public:
		static std::vector<Info> FetchInfo();

	private:
		static void TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue);
	};

}