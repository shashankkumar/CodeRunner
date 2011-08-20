#include "Logs.h"

FILE * Logs::pLogFile;
time_t Logs::rawtime;
char Logs::curtime[100];

void Logs::OpenLogFile(){
	pLogFile = fopen(LOGFILEPATH, "a");
	if(pLogFile==NULL)printf("Cannot open log file for logging.");
}

void Logs::CloseLogFile(){
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
	printf("%s", curtime);
}

void Logs::Write(const char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	fputs(logs, pLogFile);
	printf("%s", logs);
}

void Logs::Write(char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	fputs(logs, pLogFile);
	printf("%s", logs);
}

void Logs::WriteLine(const char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	fputs(logs, pLogFile);
	fputs("\n", pLogFile);
	printf("%s\n", logs);
}

void Logs::WriteLine(char* logs, bool PrintTime){
	if(PrintTime) SetAndPrintTime();
	//printf("\n%lu\n" , sizeof((*logs)));
	fputs(logs, pLogFile);
	fputs("\n", pLogFile);
	printf("%s\n", logs);
}

void Logs::GoToSleep(){
	char SleepText[50];;
	sprintf(SleepText, "Going to sleep for %d seconds.\n", SLEEPINTERVAL);
	Logs::WriteLine(SleepText);
	Logs::WriteLine("============================================================================\n");
}

void Logs::CodeRunnerStarted(){
	Logs::WriteLine("============================================================================\n");
	Logs::WriteLine("CodeRunner Started", false);
	Logs::LeaveLine();
}

void Logs::LeaveLine(){
	Logs::WriteLine("");
}
