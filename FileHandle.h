#ifndef FILEHANDLE_H
#define FILEHANDLE_H
#include "includes.h"
#include "CurlWrapper.h"
class FileHandle{
  private:
	int FileId, MemoryUsed, NoOfTestCases, TestCaseId, TimeLimit, MemoryLimit;
	float TimeUsed;
	char systemString[100], status[10], logs[10000], detailstatus[10000], str[100], *token, tmp[10], logString[100];
	char timeused[10], memoryused[10], fileid[10], command[1000];
	const char* lang, *ProblemId;
	string CompileOutput;
	CurlWrapper FileCurl;
	string ExecutionStr;
	bool result;
  public:
	FileHandle(int fileid, const char* pid, int tl, int ml, const char* l);
	~FileHandle();
	int FetchFile();
	int CheckMIME();
	int MakeDir();
	void Compile();
	void pipeCompile();
	int pipeNoOfTestCases();
	int PrepareToExecute();
	void PipeExecute();
	void Execution();
	void MatchOutput();
	void pipeMatch();
	void SendResults();
	void CleanUp();
	
	bool getResult();
	void FileOperations();
	void Action();

};
#endif
