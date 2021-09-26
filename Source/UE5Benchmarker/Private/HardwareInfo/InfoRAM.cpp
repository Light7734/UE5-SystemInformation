#include "InfoRAM.h"
#include "systemcommand.h"

namespace HardwareInfo {

	std::vector<FRAM::Info> FRAM::FetchInfo()
	{
		// query rams
		FSystemCommand ramsQuery("wmic path Win32_PhysicalMemory get /format: list");
		if (ramsQuery.HasFailed())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to query RAMs"));
			return {};
		}

		// fetch rams info
		std::vector<Info> ramsInfo;
		Info ramInfo;

		uint32_t index = 1u;
		for (auto it : ramsQuery.GetResult())
		{
			TryFetchField(it, "Capacity=", ramInfo.Capacity);
			TryFetchField(it, "ConfiguredClockSpeed=", ramInfo.ConfiguredClockSpeed);
			TryFetchField(it, "ConfiguredVoltage=", ramInfo.ConfiguredVoltage);
			TryFetchField(it, "DataWidth=", ramInfo.DataWidth);
			TryFetchField(it, "DeviceLocator=", ramInfo.DeviceLocator);
			TryFetchField(it, "FormFactor=", ramInfo.FormFactor);
			TryFetchField(it, "InterleaveDataDepth=", ramInfo.InterleaveDataDepth);
			TryFetchField(it, "InterleavePosition=", ramInfo.InterleavePosition);
			TryFetchField(it, "Manufacturer=", ramInfo.Manufacturer);
			TryFetchField(it, "MaxVoltage=", ramInfo.MaxVoltage);
			TryFetchField(it, "MinVoltage=", ramInfo.MinVoltage);
			TryFetchField(it, "PartNumber=", ramInfo.PartNumber);
			TryFetchField(it, "SMBIOSMemoryType=", ramInfo.SMBIOSMemoryType);
			TryFetchField(it, "Speed=", ramInfo.Speed);
			TryFetchField(it, "Tag=", ramInfo.Tag);
			TryFetchField(it, "TotalWidth=", ramInfo.TotalWidth);
			TryFetchField(it, "TypeDetail=", ramInfo.TypeDetail);

			if (it.find("Version") == 0u)
			{
				ramInfo.Index = index++;

				// store current ram info then reset it
				ramsInfo.push_back(ramInfo);
				ramInfo = Info();
			}
		}

		return ramsInfo;
	}

	void FRAM::TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue)
	{
		if (outValue != INFO_STR_UNKNOWN)
			return;

		outValue = iter.find(fieldName) != std::string::npos ? iter.substr(iter.find(fieldName) + std::strlen(fieldName)) : INFO_STR_UNKNOWN;

		if (outValue == "")
			outValue = INFO_STR_UNKNOWN;
	}

	std::string FRAM::DetermineMemoryType(const std::string& memoryTypeString)
	{
		int memoryType = 0;
		try {
			memoryType = std::stoi(memoryTypeString);
		}
		catch (std::exception& e) {
			(void)e;
			memoryType = 0;
		}

		// https://msdn.microsoft.com/en-us/library/aa394347(v=vs.85).aspx
		switch (memoryType)
		{
		case 0: return INFO_STR_UNKNOWN;
		case 1: return "Other";
		case 2: return "DRAM";
		case 3: return "Synchronous DRAM";
		case 4: return "Cache DRAM";
		case 5: return "EDO";
		case 6: return "EDRAM";
		case 7: return "VRAM";
		case 8: return "SRAM";
		case 9: return "RAM";
		case 10: return "ROM";
		case 11: return "Flash";
		case 12: return "EEPROM";
		case 13: return "FEPROM";
		case 14: return "EPROM";
		case 15: return "CDRAM";
		case 16: return "3DRAM";
		case 17: return "SDRAM";
		case 18: return "SGRAM";
		case 19: return "RDRAM";
		case 20: return "DDR1";
		case 21: return "DDR2";
		case 22: return "DDR2 - FBDIMM";
		case 23: return "DDR2 - FBDIMM";
		case 24: return "DDR3";
		case 25: return "FBD2";
		default: return INFO_STR_UNKNOWN;
		}
	}

	std::string FRAM::DetermineFormFactor(const std::string& formFactorString)
	{
		int formFactor = 0;
		try
		{
			formFactor = std::stoi(formFactorString);
		}
		catch (std::exception& e)
		{
			(void)e;
			formFactor = 0;
		}

		// https://msdn.microsoft.com/en-us/library/aa394347(v=vs.85).aspx
		switch (formFactor) {
		case 0: return INFO_STR_UNKNOWN;
		case 1: return "Other";
		case 2: return "SIP";
		case 3: return "DIP";
		case 4: return "ZIP";
		case 5: return "SOJ";
		case 6: return "Proprietary";
		case 7: return "SIMM";
		case 8: return "DIMM";
		case 9: return "TSOP";
		case 10: return "PGA";
		case 11: return "RIMM";
		case 12: return "SODIMM";
		case 13: return "SRIMM";
		case 14: return "SMD";
		case 15: return "SSMP";
		case 16: return "QFD";
		case 17: return "TQFP";
		case 18: return "SOIC";
		case 19: return "LCC";
		case 20: return "PLCC";
		case 21: return "BGA";
		case 22: return "FPBGA";
		case 23: return "LGA";
		default: return INFO_STR_UNKNOWN;
		}
	}

}