#ifndef FILEINFO_H
#define FILEINFO_H

struct FileInfoStruct{
	int FileId;
	int TimeLimit;
	int MemoryLimit;
	char ProblemId[11];
	char lang[11];
};

struct FileInfoFetchOptionsStruct{
	bool f, p, l, b;
	FileInfoStruct FileInfo;
	void Init(){
		f=p=l=b=false;
	}
};

#endif
