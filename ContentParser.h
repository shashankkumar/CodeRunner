#ifndef CONTENTPARSER_H
#define CONTENTPARSER_H
#include "includes.h"
#include "CurlWrapper.h"
#include "Logs.h"

struct FileInfoStruct{
	int FileId;
	int TimeLimit;
	int MemoryLimit;
	char ProblemId[11];
	char lang[11];
};

class ContentParser{
  private:
	char* FileInfoListStr;
	int Ix;
	FileInfoStruct FileInfo;
	
  public:
	
	int FetchFileInfoList();
	char read_char();
	int read_int();
	void read_char_str(char *);
	bool EndOfContent();
	FileInfoStruct GetNextFileInfo();
};
#endif
