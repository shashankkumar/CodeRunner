#include "Logs.h"

FILE * Logs::pLogFile = fopen(LOGFILEPATH, "a");
time_t Logs::rawtime;
char Logs::curtime[100];

void Logs::OpenLogFile(){
	if(pLogFile==NULL)
		pLogFile = fopen(LOGFILEPATH, "a");
}

void Logs::CloseLogFile(){
	if(pLogFile!=NULL)
		fclose(pLogFile);
}

void Logs::SetTime(){
	time( &rawtime );
	strcpy(curtime, ctime(&rawtime));
	int l = strlen(curtime);
	//curtime[l-5]='\0';
}

void Logs::SetAndPrintTime(){
	time( &rawtime );
	strcpy(curtime, ctime(&rawtime));
	int l = strlen(curtime);
	//curtime[l-5]='\0';
	fwrite(curtime, 1, sizeof(curtime), pLogFile);
}

void Logs::Write(const char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	fwrite(logs, 1, sizeof(logs), pLogFile);
}

void Logs::Write(char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	fwrite(logs, 1, sizeof(logs), pLogFile);
}

void Logs::WriteLine(const char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	fwrite(logs, 1, sizeof(logs), pLogFile);
	fwrite("\n", 1, 1, pLogFile);
}

void Logs::WriteLine(char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	fwrite(logs, 1, sizeof(logs), pLogFile);
	fwrite("\n", 1, 1, pLogFile);
}

