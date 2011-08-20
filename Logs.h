#ifndef LOGS_H
#define LOGS_H
#include "includes.h"

class Logs{
  private:
  	static FILE * pLogFile;
  	static time_t rawtime;
  	static char curtime[100];
  public:
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
	static void GoToSleep();
	static void CodeRunnerStarted();
};
#endif
