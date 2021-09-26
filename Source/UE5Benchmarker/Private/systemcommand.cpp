#include "SystemCommand.h"

FSystemCommand::FSystemCommand(const char* command)
{
	FILE* fp = _popen(command, "r");
	std::string path(1024, NULL);

	if (!fp)
	{
		UE_LOG(LogTemp, Log, TEXT("ERROR: Failed to execute system command: \"%s\""), *FString(command));
		bFailed = true;
		return;
	}

	while (fgets(&path[0], 1024, fp))
		Result.push_back(path.substr(0, path.find("\r\n")));

	bFailed = !!_pclose(fp);
}