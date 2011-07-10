#include "includes.h"
#include "ContentParser.h"

int ContentParser::FetchFileIdList(){
	CurlWrapper *CurlVar = new CurWrapper();
	string strContent;
		
	if(CurlVar->FetchContentFromWebPage(&strContent) == -1) {
		delete CurlVar;		//Clean up
	   	return -1;
	}
	    
	FileInfoListStr = new char[strContent.size() + 1];
	strcpy(FileInfoListStr, strContent.c_str());
	Ix = 0;
	delete CurlVar;
	return 0;
}

char read_char() {
	return FileInfoListStr[ Ix++ ];
}

int read_int(){
	char c; int ret;
          
    while( !isdigit( c = read_char() ) );
    ret = c - '0';

    while(  isdigit( c = read_char() ) )
	    ret = ( ret * 10 + c - '0' );
}

void read_char_str(char * ret)

	for(int i=0;i<10 && isalnum(FileInfoListStr[Ix]) ;Ix++, i++){
		ret[i] = FileInfoListStr[Ix];
	}
	ret[i]='\0';
}

void GetNextFileInfo(){
	FileInfo.FileId = read_int();
	read_char_str(FileInfo.ProblemId);
	FileInfo.TimeLimit = read_int();
	FileInfo.MemoryLimit = read_int();
	read_char_str(FileInfo.lang);
}

