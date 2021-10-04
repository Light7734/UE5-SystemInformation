#pragma once

#include "CoreMinimal.h"

#include <string>

#define INFO_STR_UNKNOWN "N/A"
#define INFO_B_TO_GB(bytes) bytes / 1000000.0 / 1000.0

#define INFO_DECIMAL_POINTS 2.0

DECLARE_LOG_CATEGORY_EXTERN(LogSystemInfo, Log, All)

enum class ESysdtemInfoDataUnit
{
	Byte = 1000000000,
	KiloByte = 1000000,
	MegaByte = 1000,
	GigaByte = 1,
};

static const char* ConvertDataUnits(const FString& value, ESysdtemInfoDataUnit valueUnit, ESysdtemInfoDataUnit outUnit = ESysdtemInfoDataUnit::GigaByte)
{
	try
	{
		// convert value
		double valueInt = FCString::Atod(*value);
		double t = (double)valueUnit / (double)outUnit;
		double outInt = std::floor((valueInt / t) * std::pow(10.0, INFO_DECIMAL_POINTS)) / std::pow(10.0, INFO_DECIMAL_POINTS);

		std::string outStr = std::to_string(outInt);
		outStr = outStr.substr(0ull, outStr.find('.') + static_cast<size_t>(INFO_DECIMAL_POINTS) + 1ull);


		// determine suffix
		const char* suffix = "";
		switch (outUnit)
		{
		case ESysdtemInfoDataUnit::Byte: suffix = " Bytes"; break;
		case ESysdtemInfoDataUnit::KiloByte: suffix = " KB"; break;
		case ESysdtemInfoDataUnit::MegaByte: suffix = " MB"; break;
		case ESysdtemInfoDataUnit::GigaByte: suffix = " GB"; break;
		}

		return (outStr + suffix).c_str();
	}
	catch (std::exception e)
	{
		(void)e;
		UE_LOG(LogTemp, Error, TEXT("Failed to convert data units: %s "), *value);
		return INFO_STR_UNKNOWN;
	}
}