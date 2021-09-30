# UE5-SystemInformation
A system information collector module for unreal engine

## Supported Platforms
* Windows

## Getting Started
1. *Run* `git clone https://github.com/light3039/ue5-systeminformation <YOUR_PROJECT_PATH/Source>`
2. Add "SystemInformation" to [YOUR_PROJECT_NAME].Build.cs's `PublicDependencyModuleNames.AddRange...`
3. Add "SystemInformation" to [YOUR_PROJECT_NAME].Target.cs's `ExtraModuleNames.AddRange...`
4. Add the following text to [YOUR_PROJECT_NAME].uproject's Modules
`		{
			"Name": "SystemInformation",
			"Type": "Runtime"
		}`
5. Restart the Unreal Editor
6. Tools -> Refresh Visual Studio Project
