#include "includes.h"
#include "ContentParser.h"

int ContentParser::FetchFileInfoList(FileInfoFetchOptionsStruct* FileInfoFetchOptions){
	CurlWrapper *CurlVar = new CurlWrapper();
	string strContent;
		
	if(CurlVar->FetchContentFromWebPage(FileInfoFetchOptions, &strContent) == -1) {
		delete CurlVar;		//Clean up
	   	return -1;
	}
	    
	FileInfoListStr = new char[strContent.size() + 1];
	FileInfo = new FileInfoStruct();
	strcpy(FileInfoListStr, strContent.c_str());
	
	Logs::WriteLine(FileInfoListStr);
	
	Ix = 0;
	delete CurlVar;
	return 0;
}

char ContentParser::read_char() {
	return FileInfoListStr[ Ix++ ];
}

int ContentParser::read_int(){
	char c; int ret;
          
    while( !isdigit( c = read_char() ) );
    ret = c - '0';

    while(  isdigit( c = read_char() ) )
	    ret = ( ret * 10 + c - '0' );
	
	return ret;
}

void ContentParser::read_char_str(char * ret){
	int i;
	for(i=0;i<10 && isalnum(FileInfoListStr[Ix]) ;Ix++, i++){
		ret[i] = FileInfoListStr[Ix];
	}
	ret[i]='\0';
}

bool ContentParser::EndOfContent(){
	while(true){
		if(isdigit(FileInfoListStr[Ix])) return false;
		else if(FileInfoListStr[Ix] == '\0') return true;
		Ix++;
	}
}

FileInfoStruct* ContentParser::GetNextFileInfo(){
	FileInfo->FileId = read_int();
	read_char_str(FileInfo->ProblemId);
	FileInfo->TimeLimit = read_int();
	FileInfo->MemoryLimit = read_int();
	read_char_str(FileInfo->lang);
	//printf("%d %s %d %d %s\n", FileInfo.FileId, FileInfo.ProblemId, FileInfo.TimeLimit, FileInfo.MemoryLimit, FileInfo.lang);
	return FileInfo;
	
}

