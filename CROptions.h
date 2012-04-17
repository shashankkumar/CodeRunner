#ifndef CROPTIONS_H
#define CROPTIONS_H
#ifndef CONFIG_H
#define CONFIG_H
#include "config.h"
#endif
#include "headers.h"


struct FileInfoStruct{
	int FileId;
	int TimeLimit;
	int MemoryLimit;
	char ProblemId[25];
	char lang[11];
};


class CROptions{
  public:
	struct FileInfoFetchOptionsStruct{
		bool FileId_Predefined, ProblemId_Predefined, Lang_Predefined;
		bool TimeLimit_Predefined, MemoryLimit_Predefined;
		FileInfoStruct FileInfo;
		FileInfoFetchOptionsStruct(){
			FileId_Predefined = ProblemId_Predefined = Lang_Predefined = false;
			TimeLimit_Predefined = MemoryLimit_Predefined = false;
			FileInfo.FileId = 0;
		};
	};
	
	static CROptions::FileInfoFetchOptionsStruct* FileInfoFetchOptions;
	static bool RunOnce;
	static bool SleepInterval;
	static const char* PATH;
	static const char* TestCasesPath;
	static const char* URLToGetFileIds;
	static const char* URLToSendResults;
	static const char* FilesPath;
	static const char* URLToGetSourceCode;
	static const char* LogFilePath;
	static const char* LogFileName;
	static const char* httpAddress;
	static const char* username;
	static const char* password;
	static bool ForcePushResult;
	static bool GetAllFileIds;
	static bool SendResults;
	static bool Clean;
	static bool SendOptions;
	static bool DownloadSourceFile;
	static bool OneFileExecution;
	static bool PrintOnScreen;
};



#endif
