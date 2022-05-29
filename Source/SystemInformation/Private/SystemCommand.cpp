#include "SystemCommand.h"

FSystemCommand::FSystemCommand(const char* command)
{
#if defined(__linux__)
	UE_LOG(Logtemp, Error, TEXT("Linux is currently not supported!"));
	bFailed = true;
	return;
	
	FILE* fp = popen(command, "r");
	std::string path(1024, '\0');
	
	if(!fp)
	{
		UE_LOG(LogTemp, Log, TEXT("ERROR: Failed to execute system command: \"%s\""), *FString(command));
		bFailed = true;
		return;
	}

	while (fgets(&path[0], 1024, fp))
	{
		Result.Push(FString(path.substr(0, path.find("\n")).c_str()));
	}

	for(auto res : Result)
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *res);
	}

	bFailed = !!pclose(fp);

#elif defined(_WIN32)
	FILE* fp = _popen(command, "r");
	std::string path(1024, NULL);

	if (!fp)
	{
		UE_LOG(LogTemp, Log, TEXT("ERROR: Failed to execute system command: \"%s\""), *FString(command));
		bFailed = true;
		return;
	}

	while (fgets(&path[0], 1024, fp))
	{
		Result.Push(FString(path.substr(0, path.find("\r\n")).c_str()));
	}

	bFailed = !!_pclose(fp);
#endif
}