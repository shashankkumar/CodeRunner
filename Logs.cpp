#include "Logs.h"

Logs::Logs(){
	logFile = fopen("logs.txt", "a");
}

Logs::Logs(int FileId){
	logFile = fopen(LOGFILEPATH, "a");
}


