#ifndef LOGS_H
#define LOGS_H
#include "includes.h"

class Logs{
  private:
  int FileId;
  static File * pLogFile;
  static time_t rawtime;
  static char curtime[100];
  public:
	Logs();
	static void ToLogs(const char* logs);
	static void ToLogs(char* logs);
	static void SetTime();
	static void SetAndPrintTime();
	static void SetFileId(int FileId);
	~Logs();
	
};
#endif
