#ifndef FILEHANDLE_H
#define FILEHANDLE_H
#include "includeh.h"
#include "CurlWrapper.h"
#include "FileInfo.h"

class FileHandle{
  private:
	int FileId, MemoryUsed, NoOfTestCases, TestCaseId, TimeLimit, MemoryLimit;
	float TimeUsed;
	char systemString[100];
	char status[10], logs[10000], detailstatus[10000];
	char str[100], *token, tmp[10];
	char logString[100];
	char TestCaseExecutionTime[10], TestCaseExecutionMemory[10];
	char FileDirAddr[100], FileAddr[100], FileName[10], FullFileAddr[100], timeused[10], memoryused[10], fileid[10];
	char command[1000];
	const char* lang, *ProblemId;
	string CompileOutput;
	CurlWrapper FileCurl;
	string ExecutionStr;
	bool result;
	FileInfoStruct* FileInfo;
  public:
	FileHandle(FileInfoStruct* FileInfo);
	~FileHandle();
	int FetchFile();
	int CheckMIME();
	int MakeDir();
	void Compile();
	void pipeCompile();
	int pipeNoOfTestCases();
	int PrepareToExecute();
	void PipeExecute();
	void Execute();
	void MatchOutput();
	void pipeMatch();
	void SendResults();
	void CleanUp();
	static bool Clean;
	static bool SendResultsVar;
	static bool DownloadSourceFile;
	
	bool getResult();
	void FileOperations();
	void Action();

};
#endif
