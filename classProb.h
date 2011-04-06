#include "includes.h"

class FileHandle{
  private:
	int FileId, MemoryUsed, NoOfInputFiles, TestCaseId, TimeLimit, MemoryLimit;
	float TimeUsed;
	char systemString[100], status[10], logs[100], detailStatus[10000], str[100], *token, tmp[10], logString[100];
	char timeused[10], memoryused[10], fileid[10], command[1000];
	const char* lang, *ProblemId;
	bool result;
	string CompileOutput;
	CurlWrapper FileCurl;
	string ExecutionStr;
  public:
	FileHandle(int fileid, const char* pid, const char* l);
	int FetchFile();
	int MakeDir();
	void Compile();
	void pipeCompile();
	int pipeNoOfInputFiles();
	int PrepareToExecute();
	void PipeExecute();
	void Execution();
	void MatchOutput();
	void pipeMatch();
	void SendResults();
	void CleanUp();
};
