#ifndef CONTENTPARSER_H
#define CONTENTPARSER_H
#include "includes.h"
#include "CurlWrapper.h"

struct FileInfoStruct{
	int FileId;
	int TimeLimit;
	int MemoryLimit;
	char ProblemId[11];
	char lang[11];
};

class ContentParser{
  private:
	static char* FileInfoListStr;
	static int Ix;
	FileInfoStruct FileInfo;
	
  public:
	static int FetchFileIdList()
	static void GetNextFileInfo();
};
#endif
