/**************************************************************************
CodeRunner - the online judge
Author: Shashank Kumar <shashankkumar.me@gmail.com>
Copyright (c): 2011 All rights reserved
Version: 1.5

 * This is a free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
  
You may contact the author of CodeRunner by e-mail at:
shashankkumar.me@gmail.com

****************************************************************************/
#include "includeh.h"
#include "FileInfo.h"
#include "ContentParser.h"
#include "FileHandle.h"

int main(int argc, char* argv[])
{
	
	if(chdir(PATH)==-1)
	{
		printf("%d\n", errno);
		printf("IE ERROR Cannot change directory to the one specified in config.h");
		return 1;
	}
	
	int opt;
	FileInfoFetchOptionsStruct* FileInfoFetchOptions = new FileInfoFetchOptionsStruct();
	FileInfoFetchOptions->Init();
	while((opt = getopt(argc, argv, "cbf:p:l:")) != -1){
		switch(opt){
			case 'f':
				FileInfoFetchOptions->f=true;
				FileInfoFetchOptions->FileInfo.FileId = atoi(optarg);
			break;
			case 'p':
				FileInfoFetchOptions->p=true;
				strcpy(FileInfoFetchOptions->FileInfo.ProblemId, optarg);
			break;
			case 'l':
				FileInfoFetchOptions->l=true;
				strcpy(FileInfoFetchOptions->FileInfo.lang, optarg);
			break;
			case 'b':
				CurlWrapper::ForcePushResult=true;
			break;
			case 'c':
				FileHandle::Clean=true;
			break;
			default: /* '?' */
				fprintf(stderr, "Usage: %s [-f fileid | [-p problemcode] [-l language]] [-b]", argv[0]); 
				exit(EXIT_FAILURE);
		}
	}
	
	if(FileInfoFetchOptions->f && (FileInfoFetchOptions->p || FileInfoFetchOptions->l)){
		fprintf(stderr, "Usage: %s [-f fileid | [-p problemcode] [-l language]] [-b]", argv[0]); 
		exit(EXIT_FAILURE);
	}
	
	Logs::OpenLogFile();
	Logs::CodeRunnerStarted();
	Logs::CloseLogFile();
	do{
		Logs::OpenLogFile();
		bool CurrentIteration = true;
		ContentParser *ContentVar = new ContentParser();
		if(ContentVar->FetchFileInfoList(FileInfoFetchOptions)==-1){
			CurrentIteration = false;
		}
		
		if(CurrentIteration && ContentVar->EndOfContent()){
			Logs::WriteLine("File Queue Empty. Nothing to evaluate.");
			CurrentIteration = false;
		}
		
		while(CurrentIteration && !ContentVar->EndOfContent()){
			FileInfoStruct* FileInfo = ContentVar->GetNextFileInfo();
			FileHandle F(FileInfo);
			F.Action();
			//delete FileInfo;
		}
		
		if(CurrentIteration) Logs::WriteLine("Current batch of files evaluated.");
		
		delete ContentVar;
		Logs::GoToSleep();
		Logs::CloseLogFile();
		sleep(SLEEPINTERVAL);
		
	}while(!RUNONCE);
		
    return 0;
}
