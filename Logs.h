#ifndef LOGS_H
#define LOGS_H
#include "includes.h"

class Logs{
  private:
  public:
	Logs();
	Logs(int FileId);
	ToLogs(const char* logs);
	ToLogs(char* logs);
	~Logs();
};
#endif
