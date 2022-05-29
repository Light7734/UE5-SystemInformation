#pragma once

#include "CoreMinimal.h"

#include <string>

#define INFO_STR_UNKNOWN "N/A"
#define INFO_B_TO_GB(bytes) bytes / 1000000.0 / 1000.0

#define INFO_DECIMAL_POINTS 2.0

DECLARE_LOG_CATEGORY_EXTERN(LogSystemInfo, Log, All)

enum class ESystemInfoDataUnit : uint64_t
{
	GigaByte = 1u,
	MegaByte = GigaByte * 1024u,
	KiloByte = MegaByte * 1024u,
	Byte = KiloByte * 1024u,
};

static FString ConvertDataUnits(const FString& valueStr, ESystemInfoDataUnit valueUnit, ESystemInfoDataUnit outUnit = ESystemInfoDataUnit::GigaByte)
{
	try
	{
		// convert value
		double valueNumeric = FCString::Atod(*valueStr);
		double t = (double)valueUnit / (double)outUnit;
		double outNumeric = ::floor((valueNumeric / t) * std::pow(10.0, INFO_DECIMAL_POINTS)) / std::pow(10.0, INFO_DECIMAL_POINTS);

		std::string outStr = std::to_string(outNumeric);
		outStr = outStr.substr(0ull, outStr.find('.') + static_cast<size_t>(INFO_DECIMAL_POINTS) + 1ull);

		// determine suffix
		const char* suffix = "";
		switch (outUnit)
		{
		case ESystemInfoDataUnit::Byte: suffix = " Bytes"; break;
		case ESystemInfoDataUnit::KiloByte: suffix = " KB"; break;
		case ESystemInfoDataUnit::MegaByte: suffix = " MB"; break;
		case ESystemInfoDataUnit::GigaByte: suffix = " GB"; break;
		}

		auto out = outStr + suffix;
		return FString(out.c_str());
	}
	catch (std::exception e)
	{
		(void)e;
		UE_LOG(LogTemp, Error, TEXT("Failed to convert data units: %s "), *valueStr);
		return INFO_STR_UNKNOWN;
	}
}