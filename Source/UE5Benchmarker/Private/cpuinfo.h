#pragma once

#include "systemcommand.h"

class CPUInfo
{
public:
	CPUInfo(const std::vector<std::string> &rawData, int cpuNumber);
    std::string name() const;
    std::string manufacturer() const;
	std::string numberOfCores() const;
    std::string architecture() const;
    std::string L2CacheSize() const;
    std::string L3CacheSize() const;
	std::string currentTemperature() const;
	std::string currentClockSpeed() const;
	int cpuNumber() const;

private:
    std::string _name;
    std::string _manufacturer;
    std::string _numberOfCores;
    std::string _architecture;
    std::string _L2CacheSize;
    std::string _L3CacheSize;
	int _cpuNumber;

    int kelvinToCelcius(int tempInKelvin) const;
    std::string getArchitecture(std::string &dataWidth) const;
	
    template <typename T> 
	std::string toString(const T &convert) const
    {
        std::stringstream transfer;
        std::string returnString;
        transfer << convert;
        transfer >> returnString;
        return returnString;
    }

	static const std::string TEMPERATURE_ERROR_IDENTIFIER_STRING;
	static const std::string NAME_IDENTIFIER_STRING;
	static const std::string NUMBER_OF_CORES_IDENTIFIER_STRING;
	static const std::string MANUFACTURER_IDENTIFIER_STRING;
	static const std::string CURRENT_CLOCK_SPEED_IDENTIFIER_STRING;
	static const std::string ARCHITECTURE_IDENTIFIER_STRING;
	static const std::string L2_CACHE_SIZE_IDENTIFIER_STRING;
	static const std::string L3_CACHE_SIZE_IDENTIFIER_STRING;
};