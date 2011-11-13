#ifndef FILEINFO_H
#define FILEINFO_H

struct FileInfoStruct{
	int FileId;
	int TimeLimit;
	int MemoryLimit;
	char ProblemId[11];
	char lang[11];
};
#endif
