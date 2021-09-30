# UE5-SystemInformation
A system information collector module for unreal engine

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

## Getting Started
1. *Run* `git clone https://github.com/light3039/ue5-systeminformation <YOUR_PROJECT_PATH/Source>`
2. Add `"SystemInformation"` to [PROJECT_NAME].Build.cs `PublicDependencyModuleNames.AddRange...`
3. Add `"SystemInformation"` to [PROJECT_NAME].Target.cs `ExtraModuleNames.AddRange...`
4. Add `{ Name": "SystemInformation", "Type": "Runtime" }` to [PROJECT_NAME].uproject's Module section
5. Restart the Unreal Editor
6. Tools -> Refresh Visual Studio Project

### Sample output:
```
Motherboard #1 {
    Manufacturer = ASUSTeK COMPUTER INC.
    Product = ROG MAXIMUS XII HERO (WI-FI)
    Status = OK
    Version = Rev 1.xx
}

Operating System #1 {
    BuildNumber = 19043
    BuildType = Multiprocessor Free
    DataExecutionPrevention_32BitApplications = TRUE
    DataExecutionPrevention_Available = TRUE
    DataExecutionPrevention_Drivers = TRUE
    DataExecutionPrevention_SupportPolicy = Opt In
    Distributed = FALSE
    ForegroundApplicationBoost = Maximum
    FreePhysicalMemory = 17.35 GB
    FreeSpaceInPagingFiles = 4.85 GB
    FreeVirtualMemory = 12.87 GB
    Manufacturer = Microsoft Corporation
    MaxNumberOfProcesses = 4294967295
    MaxProcessMemorySize = 137438.95 GB
    OSArchitecture = 64-bit
    PortableOperatingSystem = FALSE
    Primary = TRUE
    ProductType = Work Station
    Status = OK
    TotalVirtualMemorySize = 38.41 GB
    TotalVisibleMemorySize = 33.43 GB
    Version = 10.0.19043
}

CPU #1 {
    Architecture = x64
    Availability = Running/Full Power
    Caption = Intel64 Family 6 Model 165 Stepping 5
    Characteristics = 252
    CpuStatus = 1
    CurrentClockSpeed = 2808
    CurrentVoltage = 9
    Description = Intel64 Family 6 Model 165 Stepping 5
    DeviceID = CPU0
    ExtClock = 100
    Family = Intel(R) Core(TM) i9 processor
    L2CacheSize = 2560
    L3CacheSize = 20480
    LoadPercentage = 1
    Manufacturer = GenuineIntel
    MaxClockSpeed = 2808
    NumberOfCores = 10
    NumberOfEnabledCore = 10
    NumberOfLogicalProcessors = 20
    SecondLevelAddressTranslationExtensions = FALSE
    SocketDesignation = LGA1200
    Status = OK
    ThreadCount = 20
}

GPU #1 {
    AdapterCompatibility = NVIDIA
    AdapterDACType = Integrated RAMDAC
    AdapterRAM = 4.29 GB
    Availability = Running/Full Power
    Caption = NVIDIA GeForce RTX 3060
    CurrentBitsPerPixel = 32
    CurrentHorizontalResolution = 2560
    CurrentNumberOfColors = 4294967296
    CurrentRefreshRate = 59
    CurrentScanMode = Non Interlaced
    CurrentVerticalResolution = 1440
    Description = NVIDIA GeForce RTX 3060
    DeviceID = VideoController1
    DriverDate = 20210805000000.000000-000
    DriverVersion = 30.0.14.7168
    InfFilename = oem45.inf
    InfSection = Section182
    InstalledDisplayDrivers = C:\Windows\System32\DriverStore\FileRepository\nv_dispsi.inf_amd64_608fde4925c44666\nvldumdx.dll,C:\Windows\System32\DriverStore\FileRepository\nv_dispsi.inf_amd64_608fde4925c44666\nvldumdx.dll,C:\Windows\System32\DriverStore\FileRepository\nv_dispsi.inf_amd64_608fde4925c44666\nvldumdx.dll,C:\Windows\System32\DriverStore\FileRepository\nv_dispsi.inf_amd64_608fde4925c44666\nvldumdx.dll
    MaxRefreshRate = 144
    MinRefreshRate = 29
    Monochrome = FALSE
    Name = NVIDIA GeForce RTX 3060
    Status = OK
    VideoArchitecture = VGA
    VideoMemoryType = Unknown
    VideoModeDescription = 2560 x 1440 x 4294967296 colors
    VideoProcessor = NVIDIA GeForce RTX 3060
}

RAM #1 {
    Capacity = 17.17 GB
    ConfiguredClockSpeed = 2666
    ConfiguredVoltage = 1200
    DataWidth = 64
    DeviceLocator = ChannelA-DIMM2
    FormFactor = DIMM
    InterleaveDataDepth = 2
    InterleavePosition = 1
    Manufacturer = G-Skill
    MaxVoltage = 1200
    MinVoltage = 1200
    PartNumber = F4-3200C16-16GTZ    
    MinVoltage = 1200
    SMBIOSMemoryType = N/A
    Speed = 2666
    Tag = Physical Memory 1
    TotalWidth = 64
    TypeDetail = N/A
}

RAM #2 {
    Capacity = 17.17 GB
    ConfiguredClockSpeed = 2666
    ConfiguredVoltage = 1200
    DataWidth = 64
    DeviceLocator = ChannelB-DIMM2
    FormFactor = DIMM
    InterleaveDataDepth = 2
    InterleavePosition = 2
    Manufacturer = G-Skill
    MaxVoltage = 1200
    MinVoltage = 1200
    PartNumber = F4-3200C16-16GTZ    
    MinVoltage = 1200
    SMBIOSMemoryType = N/A
    Speed = 2666
    Tag = Physical Memory 3
    TotalWidth = 64
    TypeDetail = N/A
}

Hard Disk #1 {
    BytesPerSector = 512
    Capabilities {
        Random Access
        Supports Writing
    }
    Caption = XPG SPECTRIX S40G
    FirmwareRevision = VB421D57
    InterfaceType = SCSI
    Manuafacturer = (Standard disk drives)
    MediaType = Fixed hard disk media
    Model = XPG SPECTRIX S40G
    SectorsPerTrack = 63
    SerialNumber = 0000_0000_0100_0000_4CE0_0018_DD8C_9084.
    Size = 512.10 GB
    TotalCylinders = 62260
    TotalHeads = 255
    TotalSectors = 1000206900
    TotalTracks = 15876300
    TracksPerCylinder = 255
}

Hard Disk #2 {
    BytesPerSector = 512
    Capabilities {
        Random Access
        Supports Writing
    }
    Caption = WDC WD20EZBX-00AYRA0
    FirmwareRevision = 01.01A01
    InterfaceType = IDE
    Manuafacturer = (Standard disk drives)
    MediaType = Fixed hard disk media
    Model = WDC WD20EZBX-00AYRA0
    SectorsPerTrack = 63
    SerialNumber =      WD-WXT2AC0N1J68
    Size = 2000.39 GB
    TotalCylinders = 243201
    TotalHeads = 255
    TotalSectors = 3907024065
    TotalTracks = 62016255
    TracksPerCylinder = 255
}

Hard Disk #3 {
    BytesPerSector = 512
    Capabilities {
        Random Access
        Supports Writing
    }
    Caption = XPG SPECTRIX S40G
    FirmwareRevision = VB421D57
    InterfaceType = SCSI
    Manuafacturer = (Standard disk drives)
    MediaType = Fixed hard disk media
    Model = XPG SPECTRIX S40G
    SectorsPerTrack = 63
    SerialNumber = 0000_0000_0100_0000_4CE0_0018_DD8C_9084.
    Size = 512.10 GB
    TotalCylinders = 62260
    TotalHeads = 255
    TotalSectors = 1000206900
    TotalTracks = 15876300
    TracksPerCylinder = 255
}
```
