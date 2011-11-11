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
#include "includes.h"
#include "ContentParser.h"
#include "FileHandle.h"
#include "Logs.h"

int main()
{
	char cCurrentPath[FILENAME_MAX];
	if (!getcwd(cCurrentPath, sizeof(cCurrentPath)))
    {
		return errno;
    }

	if(chdir(PATH)==-1)
	{
		printf("%d\n", errno);
		printf("IE ERROR Cannot change directory to that of file");
		return 1;
	}
	if (!getcwd(cCurrentPath, sizeof(cCurrentPath)))
    {
		return errno;
    }

	Logs::OpenLogFile();
	Logs::CodeRunnerStarted();
	Logs::CloseLogFile();
	do{
		Logs::OpenLogFile();
		bool CurrentIteration = true;
		ContentParser *ContentVar = new ContentParser();
		if(ContentVar->FetchFileInfoList()==-1){
			CurrentIteration = false;
		}
		
		if(CurrentIteration && ContentVar->EndOfContent()){
			Logs::WriteLine("File Queue Empty. Nothing to evaluate.");
			CurrentIteration = false;
		}
		
		while(CurrentIteration && !ContentVar->EndOfContent()){
			FileInfoStruct FileInfo = ContentVar->GetNextFileInfo();
			FileHandle F(FileInfo.FileId, FileInfo.ProblemId, FileInfo.TimeLimit, FileInfo.MemoryLimit, FileInfo.lang);
			F.Action();
		} 
		
		if(CurrentIteration) Logs::WriteLine("Current batch of files evaluated.");
		
		delete ContentVar;
		Logs::GoToSleep();
		Logs::CloseLogFile();
		sleep(SLEEPINTERVAL);
		
	}while(!RUNONCE);
		
    return 0;
}
