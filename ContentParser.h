#ifndef CONTENTPARSER_H
#define CONTENTPARSER_H
#include "includes.h"
#include "CurlWrapper.h"
#include "Logs.h"
#include "FileInfo.h"

class ContentParser{
  private:
	char* FileInfoListStr;
	int Ix;
	FileInfoStruct* FileInfo;
	FileInfoFetchOptionsStruct* FileInfoFetchOptions;
  public:
	
	int FetchFileInfoList(FileInfoFetchOptionsStruct* FileInfoFetchOptions);
	char read_char();
	int read_int();
	void read_char_str(char *);
	bool EndOfContent();
	FileInfoStruct* GetNextFileInfo();
};
#endif
