#ifndef CROPTIONS_H
#define CROPTIONS_H
#include "../Config/config.h"
#include "headers.h"


/*---------------------------------------------Struct  Defination  Starts-----------------------------------------------------------------*/



struct FileInfoStruct
{
	int FileId;
	char ProblemId[25];
	//Unique Id by which website and CodeRunner identifies a problem. For eg. PALIN, TEST etc.
	int TimeLimit;
	int MemoryLimit;
	char lang[11]; //acceptable values `cpp, c, java`
};



/*---------------------------------------------Struct  Defination  Ends----------------------------------------------------------------------*/



class CROptions
{
  public:


  	                                    /*---------------------Struct  Defination  Starts-------------------------*/


	struct FileInfoFetchOptionsStruct
	{
		bool FileId_Predefined, ProblemId_Predefined, Lang_Predefined,TimeLimit_Predefined, MemoryLimit_Predefined;
		FileInfoStruct FileInfo;
		FileInfoFetchOptionsStruct()
		{
			FileId_Predefined = ProblemId_Predefined = Lang_Predefined = TimeLimit_Predefined = MemoryLimit_Predefined = false;
			FileInfo.FileId = 0;
		};
	};


                                        	/*------------------Struct  Defination  Ends------------------------------*/



	static CROptions::FileInfoFetchOptionsStruct* FileInfoFetchOptions;
	static bool RunOnce;
	static unsigned int SleepInterval;
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
	static bool lang_c;
	static bool lang_cpp;
	static bool lang_java;
	static bool lang_php;
	static bool lang_python;
	static bool lang_perl;
	static bool ForcePushResult;
	static bool GetAllFileIds;
	static bool SendResults;
	static bool Clean;
	static bool SendOptions;
	static bool DownloadSourceFile;
	static bool OneFileExecution;
	static bool PrintOnScreen;
	static bool Verbose;
};


#endif
