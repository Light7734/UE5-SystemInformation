#pragma once

#include <string>

#define INFO_STR_UNKNOWN "N/A"
#define INFO_B_TO_GB(bytes) bytes / 1000000.0 / 1000.0

#define INFO_DECIMAL_POINTS 2.0


namespace SystemInfo {

	enum class EDataUnit
	{
		Byte     = 1000000000,
		KiloByte = 1000000,
		MegaByte = 1000,
		GigaByte = 1,
	};

	static const char* ConvertDataUnits(const std::string& value, EDataUnit valueUnit, EDataUnit outUnit = EDataUnit::GigaByte)
	{ 
		try 
		{
			// convert value
			double valueInt = std::stoull(value);
			double t = (double)valueUnit / (double)outUnit;
			double outInt = std::floor( (valueInt / t) * std::pow(10.0, INFO_DECIMAL_POINTS) ) / std::pow(10.0, INFO_DECIMAL_POINTS);

			std::string outStr = std::to_string(outInt);
			outStr = outStr.substr(0ull, outStr.find('.') + static_cast<size_t>(INFO_DECIMAL_POINTS) + 1ull);
			

			// determine suffix
			const char* suffix = "";
			switch (outUnit)
			{
			case EDataUnit::Byte: suffix = " Bytes"; break;
			case EDataUnit::KiloByte: suffix = " KB"; break;
			case EDataUnit::MegaByte: suffix = " MB"; break;
			case EDataUnit::GigaByte: suffix = " GB"; break;
			}								 

			return (outStr + suffix).c_str();
		}
		catch(std::exception e)
		{
			(void)e;
			UE_LOG(LogTemp, Error, TEXT("Failed to convert data units: %s "), *FString(value.c_str()));
			return INFO_STR_UNKNOWN;
		}
	}

}