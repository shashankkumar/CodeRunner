/**************************************************************************
CodeRunner - the online judge
Author: Shashank Kumar <shashankkumar.me@gmail.com>
Copyright (c): 2010 All rights reserved
Version: 1.5

 * This is a free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
  
You may contact the author of CodeRunner by e-mail at:
shashankkumar.me@gmail.com

****************************************************************************/
#include "includes.h"
#include "CurlWrapper.h"
#include "FileHandle.h"

void FileThread(int FileId, const char* ProblemId, int TimeLimit, int MemoryLimit, const char* lang){
	
	FileHandle *F = new FileHandle(FileId, ProblemId, TimeLimit, MemoryLimit, lang);
	
	if(F->FetchFile()==-1) return;
	if(F->MakeDir()==-1) return;
	
	F->Compile();
	
	if(F->getResult()==true){
		if(F->PrepareToExecute()==-1){
			F->CleanUp();
			return;
		}
		F->Execute();
	}
	F->SendResults();
	//F->CleanUp();
	delete F;
}


int main(){
  while(true){
	
	// Variables declaration, initialization and memory allocation
	CurlWrapper *C = new CurlWrapper();
	string strContent;
	char *tmpContent = new char[100];
	int FileId, TimeLimit, MemoryLimit, ixS=0, ixE=0;
	char *content, *token, *ix, FileInfo[100];
	char *ProblemId=new char[10];
	char *lang = new char[10];
	
	// Processing begins
	if(C->FetchContentFromWebpage(&strContent) == -1){
		delete C;	//Clean up
		ToLogs("Going to sleep for 5 seconds");
		sleep(5);
		continue;
	}
	
	content = new char[strContent.size() + 1];
	sprintf(content, "%s", strContent.c_str());
	ToLogs(content);		// Output fetched content on to the logs
	
	char logs[100];
	while(content[ixE] != '\0'){
		
		// Finding postion of the information for next file to be graded
		while(content[ixE]!='\n' && content[ixE]!='\0')ixE++;
		if(content[ixE]=='\0')break;
		memcpy(FileInfo, content+ixS, ixE - ixS);
		FileInfo[ixE-ixS]='\0';
		while(content[ixE]=='\n')ixE++;
		ixS = ixE; 
		
		// Extracting file specific information from the recieved content of the webpage
		token = strtok(FileInfo, " \n\r");
		FileId = atoi(token); 				token = strtok(NULL, " \n\r");
		sprintf(ProblemId, "%s", token); 	token = strtok(NULL, " \n\r");
		TimeLimit = atoi(token);			token = strtok(NULL, " \n\r"); 
		MemoryLimit = atoi(token);			token = strtok(NULL, " \n\r");
		sprintf(lang, "%s", token);			
		printf("FileId: %d  ProblemId: %s  TimeLimit: %d  MemoryLimit: %d  lang: %s\n", FileId, ProblemId, TimeLimit, MemoryLimit, lang);
		
		// FileThread to carry out grading of the file
		//FileThread(FileId, ProblemId, TimeLimit, MemoryLimit, lang);
		FileHandle *F = new FileHandle(FileId, ProblemId, TimeLimit, MemoryLimit, lang);
		F->Action();
		delete F;
	}
	delete C;	//Clean up
	ToLogs("Going to sleep for 5 seconds");
	sleep(360);
  }	
  return 0;
}

