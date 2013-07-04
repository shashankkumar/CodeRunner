#ifndef LOGS_H
#define LOGS_H

#include "headers.h"
#include "CROptions.h"


class Logs{

  private:
  	static FILE * pLogFile; //File Object
  	static time_t rawtime; //Time type : as returned by time function
  	static char curtime[100];
  	static char logfile[100];
  
  public:
	static void SetLogFileName(const char* logfilepath, const char* logfilename);
	static void OpenLogFile();
	static void CloseLogFile();
	static void Write(const char* logs, bool PrintTime = false);
	static void Write(char* logs, bool PrintTime = false);
	static void WriteLine(const char* logs, bool PrintTime = false);
	static void WriteLine(char* logs, bool PrintTime = false);
	static void LeaveLine();
	static void SetTime();
	static void SetAndPrintTime();
	static void SetFileId(int FileId);
	static void CodeRunnerStarted();

};

#endif
