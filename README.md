# UE5-SystemInformation
A system information collector plugin for unreal engine

## Supported Platforms
* Windows

## What's Collected
* Motherboard
* Operating System
* CPU
* GPU
* RAM
* HardDisk

## Future of this project
* Linux support
* Temperature Info
* More details about each hardware
* XML output

## Getting Started
 
1. `git clone https://github.com/light3039/ue5-systeminformation <PROJECT_DIR>/Plugins/SystemInformation`
2. Add `"SystemInformation"` to <MODULE_NAME>.Build.cs `PublicDependencyModuleNames.AddRange...`
3. Add `"SystemInformation"` to <PROJECT_NAME>.Target.cs `ExtraModuleNames.AddRange...`
4. Compile and Restart the Unreal Editor
5. Tools -> Refresh Visual Studio Project

### Sample output:
```
{
    "Motherboard1": {
        "manufacturer": "ASUSTeK COMPUTER INC.",
        "product": "ROG MAXIMUS XII HERO (WI-FI)",
        "status": "OK",
        "version": "Rev 1.xx",
        "index": 1
    },
    "OperatingSystem1": {
        "buildNumber": "19043",
        "buildType": "Multiprocessor Free",
        "caption": "Microsoft Windows 10 Pro",
        "dataExecutionPrevention_32BitApplications": "TRUE",
        "dataExecutionPrevention_Available": "TRUE",
        "dataExecutionPrevention_Drivers": "TRUE",
        "dataExecutionPrevention_SupportPolicy": "Opt In",
        "distributed": "FALSE",
        "foregroundApplicationBoost": "Maximum",
        "freePhysicalMemory": "17.44 GB",
        "freeSpaceInPagingFiles": "4.66 GB",
        "freeVirtualMemory": "16.65 GB",
        "manufacturer": "Microsoft Corporation",
        "maxNumberOfProcesses": "4294967295",
        "maxProcessMemorySize": "131071.99 GB",
        "oSArchitecture": "64-bit",
        "portableOperatingSystem": "FALSE",
        "primary": "TRUE",
        "productType": "Work Station",
        "sizeStoredInPagingFiles": "4980736",
        "status": "OK",
        "totalVirtualMemorySize": "36.63 GB",
        "totalVisibleMemorySize": "31.88 GB",
        "version": "10.0.19043"
    },
    "CPU1": {
        "architecture": "x64",
        "availability": "Running/Full Power",
        "caption": "Intel64 Family 6 Model 165 Stepping 5",
        "characteristics": "252",
        "cpuStatus": "1",
        "currentClockSpeed": "2808",
        "currentVoltage": "9",
        "description": "Intel64 Family 6 Model 165 Stepping 5",
        "deviceId": "CPU0",
        "extClock": "100",
        "family": "Intel(R) Core(TM) i9 processor",
        "l2CacheSize": "2560",
        "l3CacheSize": "20480",
        "loadPercentage": "7",
        "manufacturer": "GenuineIntel",
        "maxClockSpeed": "2808",
        "name": "Intel(R) Core(TM) i9-10900 CPU @ 2.80GHz",
        "numberOfCores": "10",
        "numberOfEnabledCore": "10",
        "numberOfLogicalProcessors": "20",
        "secondLevelAddressTranslationExtensions": "FALSE",
        "socketDesignation": "LGA1200",
        "status": "OK",
        "threadCount": "20",
        "index": 1
    },
    "GPU1": {
        "adapterCompatibility": "NVIDIA",
        "adapterDACType": "Integrated RAMDAC",
        "adapterRAM": "3.99 GB",
        "availability": "Running/Full Power",
        "caption": "NVIDIA GeForce RTX 3060",
        "currentBitsPerPixel": "32",
        "currentHorizontalResolution": "2560",
        "currentNumberOfColors": "4294967296",
        "currentRefreshRate": "143",
        "currentScanMode": "Non Interlaced",
        "currentVerticalResolution": "1440",
        "description": "NVIDIA GeForce RTX 3060",
        "deviceId": "VideoController1",
        "driverDate": "20210805000000.000000-000",
        "driverVersion": "30.0.14.7168",
        "infFilename": "oem45.inf",
        "infSection": "Section182",
        "installedDisplayDrivers": "C:WindowsSystem32DriverStoreFileRepositorynv_dispsi.inf_amd64_608fde4925c44666nvldumdx.dll,C:WindowsSystem32DriverStoreFileRepositorynv_dispsi.inf_amd64_608fde4925c44666nvldumdx.dll,C:WindowsSystem32DriverStoreFileRepositorynv_dispsi.inf_amd64_608fde4925c44666nvldumdx.dll,C:WindowsSystem32DriverStoreFileRepositorynv_dispsi.inf_amd64_608fde4925c44666nvldumdx.dll",
        "maxRefreshRate": "143",
        "minRefreshRate": "50",
        "monochrome": "FALSE",
        "name": "NVIDIA GeForce RTX 3060",
        "status": "OK",
        "videoArchitecture": "VGA",
        "videoMemoryType": "Unknown",
        "videoModeDescription": "2560 x 1440 x 4294967296 colors",
        "videoProcessor": "NVIDIA GeForce RTX 3060",
        "index": 1
    },
    "RAM1": {
        "capacity": "16.00 GB",
        "configuredClockSpeed": "2666",
        "configuredVoltage": "1200",
        "dataWidth": "64",
        "deviceLocator": "ChannelA-DIMM2",
        "formFactor": "DIMM",
        "interleaveDataDepth": "2",
        "interleavePosition": "1",
        "manufacturer": "G-Skill",
        "maxVoltage": "1200",
        "minVoltage": "1200",
        "partNumber": "F4-3200C16-16GTZ    ",
        "sMBIOSMemoryType": "N/A",
        "speed": "2666",
        "tag": "Physical Memory 1",
        "totalWidth": "64",
        "typeDetail": "N/A",
        "index": 1
    },
    "RAM2": {
        "capacity": "16.00 GB",
        "configuredClockSpeed": "2666",
        "configuredVoltage": "1200",
        "dataWidth": "64",
        "deviceLocator": "ChannelB-DIMM2",
        "formFactor": "DIMM",
        "interleaveDataDepth": "2",
        "interleavePosition": "2",
        "manufacturer": "G-Skill",
        "maxVoltage": "1200",
        "minVoltage": "1200",
        "partNumber": "F4-3200C16-16GTZ    ",
        "sMBIOSMemoryType": "N/A",
        "speed": "2666",
        "tag": "Physical Memory 3",
        "totalWidth": "64",
        "typeDetail": "N/A",
        "index": 2
    },
    "HardDisk1": {
        "bytesPerSector": "512",
        "capabilities": [
            "Random Access",
            "Supports Writing"
        ],
        "caption": "XPG SPECTRIX S40G",
        "firmwareRevision": "VB421D57",
        "interfaceType": "SCSI",
        "manufacturer": "(Standard disk drives)",
        "mediaType": "Fixed hard disk media",
        "model": "XPG SPECTRIX S40G",
        "sectorsPerTrack": "63",
        "serialNumber": "0000_0000_0100_0000_4CE0_0018_DD8C_9084.",
        "size": "476.93 GB",
        "totalCylinders": "62260",
        "totalHeads": "255",
        "totalSectors": "1000206900",
        "totalTracks": "15876300",
        "tracksPerCylinder": "255",
        "index": 1
    },
    "HardDisk2": {
        "bytesPerSector": "512",
        "capabilities": [
            "Random Access",
            "Supports Writing",
            "Supports Removable Media"
        ],
        "caption": " USB  SanDisk 3.2Gen1 USB Device",
        "firmwareRevision": "1.00",
        "interfaceType": "USB",
        "manufacturer": "(Standard disk drives)",
        "mediaType": "Removable Media",
        "model": " USB  SanDisk 3.2Gen1 USB Device",
        "sectorsPerTrack": "63",
        "serialNumber": "050101bd5ae8db2902a9",
        "size": "114.60 GB",
        "totalCylinders": "14961",
        "totalHeads": "255",
        "totalSectors": "240348465",
        "totalTracks": "3815055",
        "tracksPerCylinder": "255",
        "index": 2
    },
    "HardDisk3": {
        "bytesPerSector": "512",
        "capabilities": [
            "Random Access",
            "Supports Writing"
        ],
        "caption": "WDC WD20EZBX-00AYRA0",
        "firmwareRevision": "01.01A01",
        "interfaceType": "IDE",
        "manufacturer": "(Standard disk drives)",
        "mediaType": "Fixed hard disk media",
        "model": "WDC WD20EZBX-00AYRA0",
        "sectorsPerTrack": "63",
        "serialNumber": "     WD-WXT2AC0N1J68",
        "size": "1863.01 GB",
        "totalCylinders": "243201",
        "totalHeads": "255",
        "totalSectors": "3907024065",
        "totalTracks": "62016255",
        "tracksPerCylinder": "255",
        "index": 3
    },
    "HardDisk4": {
        "bytesPerSector": "512",
        "capabilities": [
            "Random Access",
            "Supports Writing"
        ],
        "caption": "XPG SPECTRIX S40G",
        "firmwareRevision": "VB421D57",
        "interfaceType": "SCSI",
        "manufacturer": "(Standard disk drives)",
        "mediaType": "Fixed hard disk media",
        "model": "XPG SPECTRIX S40G",
        "sectorsPerTrack": "63",
        "serialNumber": "0000_0000_0100_0000_4CE0_0018_DD8C_9084.",
        "size": "476.93 GB",
        "totalCylinders": "62260",
        "totalHeads": "255",
        "totalSectors": "1000206900",
        "totalTracks": "15876300",
        "tracksPerCylinder": "255",
        "index": 4
    }
}
```
