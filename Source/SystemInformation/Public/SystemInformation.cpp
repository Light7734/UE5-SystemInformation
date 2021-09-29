// Created by Light3039, under MIT5 license

#include <intrin.h>

#include "InfoMotherboard.h"
#include "InfoOS.h"
#include "InfoRam.h"
#include "InfoCPU.h"
#include "InfoGPU.h"
#include "InfoHardDisk.h"

#include <Modules/ModuleManager.h>

IMPLEMENT_MODULE(FDefaultModuleImpl, SystemInformation);
// IMPLEMENT_MODULE(FDefaultModuleImpl, FOperatingSystem);
// IMPLEMENT_MODULE(FDefaultModuleImpl, FCPU);
// IMPLEMENT_MODULE(FDefaultModuleImpl, FGPU);
// IMPLEMENT_MODULE(FDefaultModuleImpl, FRAM);
// IMPLEMENT_MODULE(FDefaultModuleImpl, FHardDisk);