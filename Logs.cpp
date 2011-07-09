#include "Logs.h"

Logs::Logs(){
	pLogFile = fopen(LOGFILEPATH, "a");
}

static void Logs::SetTime(){
	time( &rawtime );
	strcpy(curtime, ctime(&rawtime));
	int l = strlen(curtime);
	//curtime[l-5]='\0';
}

static void Logs::SetAndPrintTime(){
	time( &rawtime );
	strcpy(curtime, ctime(&rawtime));
	int l = strlen(curtime);
	//curtime[l-5]='\0';
	fwrite(curtime, 1, sizeof(curtime), pLogFile);
}

static void Logs::ToLogs(const char* logs, bool PrintTime = false){
	if(PrintTime) SetAndPrintTime();
	fwrite(logs, 1, sizeof(logs), pLogFile);
}

static void Logs::ToLogs(char* logs, bool PrintTime = false){
	if(PrintTime) SetAndPrintTime();
	fwrite(logs, 1, sizeof(logs), pLogFile);
}

Logs::~Logs(){
	fclose(pLogFile);
}
