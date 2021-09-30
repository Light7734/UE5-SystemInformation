#include "InfoCPU.h"
#include "SystemCommand.h"

namespace SystemInfo {

	std::vector<FCPU::Info> FCPU::FetchInfo()
	{
		// query cpus
		FSystemCommand cpusQuery("wmic path Win32_Processor get /format: list");

		if (cpusQuery.HasFailed())
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to query CPUs"));
			return {};
		}

		// fetch cpus info
		std::vector<Info> cpusInfo;
		Info cpuInfo;

		uint32_t index = 1u;
		for (auto it : cpusQuery.GetResult())
		{
			TryFetchField(it, "Architecture=", cpuInfo.Architecture);
			TryFetchField(it, "Availability=", cpuInfo.Availability);
			TryFetchField(it, "Caption=", cpuInfo.Caption);
			TryFetchField(it, "Characteristics=", cpuInfo.Characteristics);
			TryFetchField(it, "CpuStatus=", cpuInfo.CpuStatus);
			TryFetchField(it, "CurrentClockSpeed=", cpuInfo.CurrentClockSpeed);
			TryFetchField(it, "CurrentVoltage=", cpuInfo.CurrentVoltage);
			TryFetchField(it, "Description=", cpuInfo.Description);
			TryFetchField(it, "DeviceID=", cpuInfo.DeviceID);
			TryFetchField(it, "ExtClock=", cpuInfo.ExtClock);
			TryFetchField(it, "Family=", cpuInfo.Family);
			TryFetchField(it, "L2CacheSize=", cpuInfo.L2CacheSize);
			TryFetchField(it, "L3CacheSize=", cpuInfo.L3CacheSize);
			TryFetchField(it, "LoadPercentage=", cpuInfo.LoadPercentage);
			TryFetchField(it, "Manufacturer=", cpuInfo.Manufacturer);
			TryFetchField(it, "MaxClockSpeed=", cpuInfo.MaxClockSpeed);
			TryFetchField(it, "Name=", cpuInfo.Name);
			TryFetchField(it, "NumberOfCores=", cpuInfo.NumberOfCores);
			TryFetchField(it, "NumberOfEnabledCore=", cpuInfo.NumberOfEnabledCore);
			TryFetchField(it, "NumberOfLogicalProcessors=", cpuInfo.NumberOfLogicalProcessors);
			TryFetchField(it, "SecondLevelAddressTranslationExtensions=", cpuInfo.SecondLevelAddressTranslationExtensions);
			TryFetchField(it, "SocketDesignation=", cpuInfo.SocketDesignation);
			TryFetchField(it, "Status=", cpuInfo.Status);

			TryFetchField(it, "ThreadCount=", cpuInfo.ThreadCount);

			if (it.find("Version=") == 0u)
			{
				cpuInfo.Index = index++;

				// translate enum values
				cpuInfo.Architecture = TranslateArchitecture(cpuInfo.Architecture);
				cpuInfo.Availability = TranslateAvailability(cpuInfo.Availability);
				cpuInfo.Family = TranslateFamiliy(cpuInfo.Family);

				// convert values
				// #todo:


				// information that could be extracted from the 'wmic' command ends here
                // insert further instructions here
                // ...


				// store current cpu info then reset it
				cpusInfo.push_back(cpuInfo);
				cpuInfo = Info();
			}
		}

		return cpusInfo;
	}

	void FCPU::TryFetchField(const std::string& iter, const char* fieldName, std::string& outValue)
	{
		if (outValue != INFO_STR_UNKNOWN)
			return;

		outValue = iter.find(fieldName) == 0u ? iter.substr(iter.find(fieldName) + std::strlen(fieldName)) : INFO_STR_UNKNOWN;

		if (outValue == "")
			outValue = INFO_STR_UNKNOWN;
	}


	const char* FCPU::TranslateArchitecture(const std::string& architecture)
	{
		try
		{
			switch (std::stoi(architecture))
			{
			case 0: return "x86";
			case 1: return "MIPS";
			case 2: return "Alpha";
			case 3: return "PowerPC";
			case 5: return "ARM";
			case 6: return "ie64";
			case 9: return "x64";
			default: return INFO_STR_UNKNOWN;
			}
		}
		catch (std::exception e)
		{
			(void)e;
			UE_LOG(LogTemp, Error, TEXT("Failed to translate cpu architecture: %s"), *FString(architecture.c_str()));
			return "";
		}
	}

	const char* FCPU::TranslateAvailability(const std::string& availability)
	{
		try
		{
			switch (std::stoi(availability))
			{
			case 1: return "Other";
			case 2: return "Unknown";
			case 3: return "Running/Full Power";
			case 4: return "Warning";
			case 5: return "In Test";
			case 6: return "Not Applicable";
			case 7: return "Power Off";
			case 8: return "Off Line";
			case 9: return "Off Duty";
			case 10: return "Degraded";
			case 11: return "Not Installed";
			case 12: return "Install Error";
			case 13: return "Power Save - Unknown";
			case 14: return "Power Save - Low Power Mode";
			case 15: return "Power Save - Standby";
			case 16: return "Power Cycle";
			case 17: return "Power Save - Warning";
			case 18: return "Paused";
			case 19: return "Not Ready";
			case 20: return "Not Configured";
			case 21: return "Quiesced";
			default: return INFO_STR_UNKNOWN;
			}
		}
		catch (std::exception e)
		{
			(void)e;
			UE_LOG(LogTemp, Error, TEXT("Failed to translate cpu availability: %s"), *FString(availability.c_str()));
			return "";
		}
	}


	const char* FCPU::TranslateFamiliy(const std::string& family)
	{
		try
		{
			switch (std::stoi(family))
			{
			case 1: return "Other";
			case 2: return "Unknown";
			case 3: return "8086 ";
			case 4: return "80286 ";
			case 5: return "80386 ";
			case 6: return "80486 ";
			case 7: return "8087 ";
			case 8: return "80287 ";
			case 9: return "80387 ";
			case 10: return "80487 ";
			case 11: return "Pentium(R) brand";
			case 12: return "Pentium(R) Pro";
			case 13: return "Pentium(R) II";
			case 14: return "Pentium(R) processor with MMX(TM) technology";
			case 15: return "Celeron(TM) ";
			case 16: return "Pentium(R) II Xeon(TM) ";
			case 17: return "Pentium(R) III";
			case 18: return "M1 Family";
			case 19: return "M2 Family";
			case 20: return "Intel(R) Celeron(R) M processor";
			case 21: return "Intel(R) Pentium(R) 4 HT processor";
			case 24: return "K5 Family";
			case 25: return "K6 Family";
			case 26: return "K6 - 2 ";
			case 27: return "K6 - 3 ";
			case 28: return "AMD Athlon(TM) Processor Family";
			case 29: return "AMD(R) Duron(TM) Processor";
			case 30: return "AMD29000 Family";
			case 31: return "K6 - 2 + ";
			case 32: return "Power PC Family";
			case 33: return "Power PC 601 ";
			case 34: return "Power PC 603 ";
			case 35: return "Power PC 603 + ";
			case 36: return "Power PC 604 ";
			case 37: return "Power PC 620 ";
			case 38: return "Power PC X704";
			case 39: return "Power PC 750 ";
			case 40: return "Intel(R) Core(TM) Duo processor";
			case 41: return "Intel(R) Core(TM) Duo mobile processor";
			case 42: return "Intel(R) Core(TM) Solo mobile processor";
			case 43: return "Intel(R) Atom(TM) processor";
			case 48: return "Alpha Family";
			case 49: return "Alpha 21064 ";
			case 50: return "Alpha 21066 ";
			case 51: return "Alpha 21164 ";
			case 52: return "Alpha 21164PC";
			case 53: return "Alpha 21164a";
			case 54: return "Alpha 21264 ";
			case 55: return "Alpha 21364 ";
			case 56: return "AMD Turion(TM) II Ultra Dual - Core Mobile M Processor Family";
			case 57: return "AMD Turion(TM) II Dual - Core Mobile M Processor Family";
			case 58: return "AMD Athlon(TM) II Dual - Core Mobile M Processor Family";
			case 59: return "AMD Opteron(TM) 6100 Series Processor";
			case 60: return "AMD Opteron(TM) 4100 Series Processor";
			case 64: return "MIPS Family";
			case 65: return "MIPS R4000";
			case 66: return "MIPS R4200";
			case 67: return "MIPS R4400";
			case 68: return "MIPS R4600";
			case 69: return "MIPS R10000";
			case 80: return "SPARC Family";
			case 81: return "SuperSPARC";
			case 82: return "microSPARC II";
			case 83: return "microSPARC IIep";
			case 84: return "UltraSPARC";
			case 85: return "UltraSPARC II";
			case 86: return "UltraSPARC IIi";
			case 87: return "UltraSPARC III";
			case 88: return "UltraSPARC IIIi";
			case 96: return "68040 ";
			case 97: return "68xxx Family";
			case 98: return "68000 ";
			case 99: return "68010 ";
			case 100: return "68020 ";
			case 101: return "68030 ";
			case 112: return "Hobbit Family";
			case 120: return "Crusoe(TM) TM5000 Family";
			case 121: return "Crusoe(TM) TM3000 Family";
			case 122: return "Efficeon(TM) TM8000 Family";
			case 128: return "Weitek";
			case 130: return "Itanium(TM) Processor";
			case 131: return "AMD Athlon(TM) 64 Processor Family";
			case 132: return "AMD Opteron(TM) Processor Family";
			case 133: return "AMD Sempron(TM) Processor Family";
			case 134: return "AMD Turion(TM) 64 Mobile Technology";
			case 135: return "Dual - Core AMD Opteron(TM) Processor Family";
			case 136: return "AMD Athlon(TM) 64 X2 Dual - Core Processor Family";
			case 137: return "AMD Turion(TM) 64 X2 Mobile Technology";
			case 138: return "Quad - Core AMD Opteron(TM) Processor Family";
			case 139: return "Third - Generation AMD Opteron(TM) Processor Family";
			case 140: return "AMD Phenom(TM) FX Quad - Core Processor Family";
			case 141: return "AMD Phenom(TM) X4 Quad - Core Processor Family";
			case 142: return "AMD Phenom(TM) X2 Dual - Core Processor Family";
			case 143: return "AMD Athlon(TM) X2 Dual - Core Processor Family";
			case 144: return "PA - RISC Family";
			case 145: return "PA - RISC 8500 ";
			case 146: return "PA - RISC 8000 ";
			case 147: return "PA - RISC 7300LC";
			case 148: return "PA - RISC 7200 ";
			case 149: return "PA - RISC 7100LC";
			case 150: return "PA - RISC 7100 ";
			case 160: return "V30 Family";
			case 161: return "Quad - Core Intel(R) Xeon(R) processor 3200 Series";
			case 162: return "Dual - Core Intel(R) Xeon(R) processor 3000 Series";
			case 163: return "Quad - Core Intel(R) Xeon(R) processor 5300 Series";
			case 164: return "Dual - Core Intel(R) Xeon(R) processor 5100 Series";
			case 165: return "Dual - Core Intel(R) Xeon(R) processor 5000 Series";
			case 166: return "Dual - Core Intel(R) Xeon(R) processor LV";
			case 167: return "Dual - Core Intel(R) Xeon(R) processor ULV";
			case 168: return "Dual - Core Intel(R) Xeon(R) processor 7100 Series";
			case 169: return "Quad - Core Intel(R) Xeon(R) processor 5400 Series";
			case 170: return "Quad - Core Intel(R) Xeon(R) processor";
			case 171: return "Dual - Core Intel(R) Xeon(R) processor 5200 Series";
			case 172: return "Dual - Core Intel(R) Xeon(R) processor 7200 Series";
			case 173: return "Quad - Core Intel(R) Xeon(R) processor 7300 Series";
			case 174: return "Quad - Core Intel(R) Xeon(R) processor 7400 Series";
			case 175: return "Multi - Core Intel(R) Xeon(R) processor 7400 Series";
			case 176: return "Pentium(R) III Xeon(TM) ";
			case 177: return "Pentium(R) III Processor with Intel(R) SpeedStep(TM) Technology";
			case 178: return "Pentium(R) 4 ";
			case 179: return "Intel(R) Xeon(TM) ";
			case 180: return "AS400 Family";
			case 181: return "Intel(R) Xeon(TM) processor MP";
			case 182: return "AMD Athlon(TM) XP Family";
			case 183: return "AMD Athlon(TM) MP Family";
			case 184: return "Intel(R) Itanium(R) 2 ";
			case 185: return "Intel(R) Pentium(R) M processor";
			case 186: return "Intel(R) Celeron(R) D processor";
			case 187: return "Intel(R) Pentium(R) D processor";
			case 188: return "Intel(R) Pentium(R) Processor Extreme Edition";
			case 189: return "Intel(R) Core(TM) Solo Processor";
			case 190: return "K7";
			case 191: return "Intel(R) Core(TM)2 Duo Processor";
			case 192: return "Intel(R) Core(TM)2 Solo processor";
			case 193: return "Intel(R) Core(TM)2 Extreme processor";
			case 194: return "Intel(R) Core(TM)2 Quad processor";
			case 195: return "Intel(R) Core(TM)2 Extreme mobile processor";
			case 196: return "Intel(R) Core(TM)2 Duo mobile processor";
			case 197: return "Intel(R) Core(TM)2 Solo mobile processor";
			case 198: return "Intel(R) Core(TM) i7 processor";
			case 199: return "Dual - Core Intel(R) Celeron(R) Processor";
			case 200: return "S / 390 and zSeries Family";
			case 201: return "ESA / 390 G4";
			case 202: return "ESA / 390 G5";
			case 203: return "ESA / 390 G6";
			case 204: return "z / Architectur base";
			case 205: return "Intel(R) Core(TM) i5 processor";
			case 206: return "Intel(R) Core(TM) i3 processor";
			case 207: return "Intel(R) Core(TM) i9 processor";
			case 210: return "VIA C7(TM) - M Processor Family";
			case 211: return "VIA C7(TM) - D Processor Family";
			case 212: return "VIA C7(TM) Processor Family";
			case 213: return "VIA Eden(TM) Processor Family";
			case 214: return "Multi - Core Intel(R) Xeon(R) processor";
			case 215: return "Dual - Core Intel(R) Xeon(R) processor 3xxx Series";
			case 216: return "Quad - Core Intel(R) Xeon(R) processor 3xxx Series";
			case 217: return "VIA Nano(TM) Processor Family";
			case 218: return "Dual - Core Intel(R) Xeon(R) processor 5xxx Series";
			case 219: return "Quad - Core Intel(R) Xeon(R) processor 5xxx Series";
			case 221: return "Dual - Core Intel(R) Xeon(R) processor 7xxx Series";
			case 222: return "Quad - Core Intel(R) Xeon(R) processor 7xxx Series";
			case 223: return "Multi - Core Intel(R) Xeon(R) processor 7xxx Series";
			case 224: return "Multi - Core Intel(R) Xeon(R) processor 3400 Series";
			case 230: return "Embedded AMD Opteron(TM) Quad - Core Processor Family";
			case 231: return "AMD Phenom(TM) Triple - Core Processor Family";
			case 232: return "AMD Turion(TM) Ultra Dual - Core Mobile Processor Family";
			case 233: return "AMD Turion(TM) Dual - Core Mobile Processor Family";
			case 234: return "AMD Athlon(TM) Dual - Core Processor Family";
			case 235: return "AMD Sempron(TM) SI Processor Family";
			case 236: return "AMD Phenom(TM) II Processor Family";
			case 237: return "AMD Athlon(TM) II Processor Family";
			case 238: return "Six - Core AMD Opteron(TM) Processor Family";
			case 239: return "AMD Sempron(TM) M Processor Family";
			case 250: return "i860";
			case 251: return "i960";
			case 254: return "Reserved(SMBIOS Extension) ";
			case 255: return "Reserved(Un - initialized Flash Content - Lo)";
			case 260: return "SH - 3 ";
			case 261: return "SH - 4 ";
			case 280: return "ARM";
			case 281: return "StrongARM";
			case 300: return "6x86";
			case 301: return "MediaGX";
			case 302: return "MII";
			case 320: return "WinChip";
			case 350: return "DSP";
			case 500: return "Video Processor";
			case 65534: return "Reserved(For Future Special Purpose Assignment)";
			case 65535: return "Reserved(Un - initialized Flash Content - Hi)";
			default: return INFO_STR_UNKNOWN;
			}
		}
		catch (std::exception e)
		{
			(void)e;
			UE_LOG(LogTemp, Error, TEXT("Failed to translate cpu family: %s"), *FString(family.c_str()));
			return "";
		}
	}

	DEFINE_LOG_CATEGORY_STATIC(SystemInfo, Log, All);
	void FCPU::Info::LogToUE_LOG() const
	{
		UE_LOG(SystemInfo, Log, TEXT("CPU #%i {"), Index);
		UE_LOG(SystemInfo, Log, TEXT("    Architecture = %s"), *FString(Architecture.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Availability = %s"), *FString(Availability.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Caption = %s"), *FString(Caption.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Characteristics = %s"), *FString(Characteristics.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    CpuStatus = %s"), *FString(CpuStatus.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    CurrentClockSpeed = %s"), *FString(CurrentClockSpeed.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    CurrentVoltage = %s"), *FString(CurrentVoltage.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Description = %s"), *FString(Description.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    DeviceID = %s"), *FString(DeviceID.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    ExtClock = %s"), *FString(ExtClock.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Family = %s"), *FString(Family.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    L2CacheSize = %s"), *FString(L2CacheSize.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    L3CacheSize = %s"), *FString(L3CacheSize.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    LoadPercentage = %s"), *FString(LoadPercentage.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Manufacturer = %s"), *FString(Manufacturer.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    MaxClockSpeed = %s"), *FString(MaxClockSpeed.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    NumberOfCores = %s"), *FString(NumberOfCores.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    NumberOfEnabledCore = %s"), *FString(NumberOfEnabledCore.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    NumberOfLogicalProcessors = %s"), *FString(NumberOfLogicalProcessors.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    SecondLevelAddressTranslationExtensions = %s"), *FString(SecondLevelAddressTranslationExtensions.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    SocketDesignation = %s"), *FString(SocketDesignation.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    Status = %s"), *FString(Status.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("    ThreadCount = %s"), *FString(ThreadCount.c_str()));
		UE_LOG(SystemInfo, Log, TEXT("}"));
	}

}