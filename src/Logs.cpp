#include "Logs.h"

FILE * Logs::pLogFile;
time_t Logs::rawtime;
char Logs::curtime[100];
char Logs::logfile[100];


void Logs::SetLogFileName(const char* logfilepath, const char* logfilename)
{
    /*Store logfilepath and logfilename to logfile array
      *A terminating null character is automatically appended after the content.
      */
	sprintf(logfile, "%s%s", logfilepath, logfilename);
}


void Logs::OpenLogFile()
{
	pLogFile = fopen(logfile, "a");
	//Open the logfile in append mode ; create if not exists
	if(pLogFile==NULL) printf("Error : Cannot open log file for logging purposes.");
}


void Logs::CloseLogFile()
{
    //close the log file
	fclose(pLogFile);
}


void Logs::SetTime()
{
	time( &rawtime );//store time value to rawtime -- returns unix time stamp
	strcpy(curtime, ctime(&rawtime));
	/*copies the current time to curtime in following format
	  *Www Mmm dd hh:mm:ss yyyy
      *Www is the weekday, Mmm the month (in letters), dd the day of the month, hh:mm:ss the time, and yyyy the year.
      *The string is followed by a new-line character ('\n') and terminated with a null-character.
      */
}


void Logs::SetAndPrintTime()
{
    Logs::SetTime()
    /*
	time( &rawtime );
	strcpy(curtime, ctime(&rawtime));
    */
	fwrite(curtime, 1, sizeof(curtime), pLogFile);
	//Write an array of sizeof(curtime) number of elements each of size 1 byte from curtime array to current postion in pLogFile
	if(CROptions::PrintOnScreen) printf("%s", curtime);
}


void Logs::Write(const char* logs, bool PrintTime)
{
	if(PrintTime) SetAndPrintTime();
	fputs(logs, pLogFile);
	//write logs string to pLogFile
	//Doesnot put new line char automatically
	if(CROptions::PrintOnScreen) printf("%s", logs);
}


void Logs::Write(char* logs, bool PrintTime)
{
	if(PrintTime) SetAndPrintTime();
	fputs(logs, pLogFile);
	if(CROptions::PrintOnScreen) printf("%s", logs);
}


void Logs::WriteLine(const char* logs, bool PrintTime)
{
    //Write and insert a line
	if(PrintTime) SetAndPrintTime();
	fputs(logs, pLogFile);
	fputs("\n", pLogFile);
	if(CROptions::PrintOnScreen) printf("%s\n", logs);
}


void Logs::WriteLine(char* logs, bool PrintTime)
{
	if(PrintTime) SetAndPrintTime();
	//printf("\n%lu\n" , sizeof((*logs)));
	fputs(logs, pLogFile);
	fputs("\n", pLogFile);
	if(CROptions::PrintOnScreen) printf("%s\n", logs);
}


void Logs::CodeRunnerStarted()
{
	Logs::WriteLine("===================================================================================================\n");
	Logs::WriteLine("CodeRunner Started", true);
	Logs::LeaveLine();
}


void Logs::LeaveLine()
{
	Logs::WriteLine("");
}
