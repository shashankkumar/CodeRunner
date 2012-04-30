#include "Logs.h"

FILE * Logs::pLogFile;
time_t Logs::rawtime;
char Logs::curtime[100];
char Logs::logfile[100];

void Logs::SetLogFileName(const char* logfilepath, const char* logfilename){
	sprintf(logfile, "%s%s", logfilepath, logfilename);
}

void Logs::OpenLogFile(){
	pLogFile = fopen(logfile, "a");
	if(pLogFile==NULL) printf("Cannot open log file for logging purposes.");
}

void Logs::CloseLogFile(){
	fclose(pLogFile);
}

void Logs::SetTime(){
	time( &rawtime );
	strcpy(curtime, ctime(&rawtime));
}

void Logs::SetAndPrintTime(){
	time( &rawtime );
	strcpy(curtime, ctime(&rawtime));

	fwrite(curtime, 1, sizeof(curtime), pLogFile);
	if(CROptions::PrintOnScreen) printf("%s", curtime);
}

void Logs::Write(const char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	fputs(logs, pLogFile);
	if(CROptions::PrintOnScreen) printf("%s", logs);
}

void Logs::Write(char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	fputs(logs, pLogFile);
	if(CROptions::PrintOnScreen) printf("%s", logs);
}

void Logs::WriteLine(const char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	fputs(logs, pLogFile);
	fputs("\n", pLogFile);
	if(CROptions::PrintOnScreen) printf("%s\n", logs);
}

void Logs::WriteLine(char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	//printf("\n%lu\n" , sizeof((*logs)));
	fputs(logs, pLogFile);
	fputs("\n", pLogFile);
	if(CROptions::PrintOnScreen) printf("%s\n", logs);
}

void Logs::CodeRunnerStarted(){
	Logs::WriteLine("============================================================================\n");
	Logs::WriteLine("CodeRunner Started", false);
	Logs::LeaveLine();
}

void Logs::LeaveLine(){
	Logs::WriteLine("");
}
