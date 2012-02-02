/**************************************************************************
CodeRunner - the online judge
Author: Shashank Kumar <shashankkumar.me@gmail.com>
Copyright (c): 2011 All rights reserved
Version: 3

Copyright Shashank Kumar. All rights reserved.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy and/or distribute copies of the Software, 
and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.  
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
	int SleepInterval = SLEEPINTERVAL;
	bool RunOnce = false, DownloadSourceFile = true;
	FileInfoFetchOptionsStruct* FileInfoFetchOptions = new FileInfoFetchOptionsStruct();
	bool UsageError = false;

	FileInfoFetchOptions->Init();

	while((opt = getopt(argc, argv, "ancdbf:r:p:l:s:w:")) != -1){
		switch(opt){
			case 'f':
				FileInfoFetchOptions->f = true;
				FileInfoFetchOptions->FileInfo.FileId = atoi(optarg);
			break;
			case 'p':
				FileInfoFetchOptions->p = true;
				strcpy(FileInfoFetchOptions->FileInfo.ProblemId, optarg);
			break;
			case 'l':
				FileInfoFetchOptions->l = true;
				strcpy(FileInfoFetchOptions->FileInfo.lang, optarg);
			break;
			case 'b':
				CurlWrapper::ForcePushResult = true;
			break;
			case 'c':
				FileHandle::Clean = true;
			break;
			case 'n':
				FileHandle::SendResultsVar = false;
			break;
			case 's':
				SleepInterval = atoi(optarg);
			break;
			case 'r':
				RunOnce = true;
			break;
			case 'd':
				FileHandle::DownloadSourceFile = false;
			break;
			case 'i':
				ContentParser::OneFileExecution = true;
			break;
			case 't':
				FileInfoFetchOptions->tl = true;
				FileInfoFetchOptions->FileInfo.TimeLimit = atoi(optarg);
			break;
			case 'm':
				FileInfoFetchOptions->ml = true;
				FileInfoFetchOptions->FileInfo.MemoryLimit = atoi(optarg);
			case 'v':
			break;
			case 'a':
				CurlWrapper::ForceGetFileIds = true;
			break;
			default: /* '?' */
				UsageError = true;
		}
	}
	
	if(FileInfoFetchOptions->f){
		if(ContentParser::OneFileExecution && (!FileInfoFetchOptions->ml || !FileInfoFetchOptions->tl || !FileInfoFetchOptions->p || !FileInfoFetchOptions->l)) UsageError = true;
		else if(!ContentParser::OneFileExecution && (FileInfoFetchOptions->p || FileInfoFetchOptions->l)) UsageError = true;
	}
	if(UsageError){
		fprintf(stderr, "Usage: %s [-f fileid [-i -p problemcode -t timelimit -m memorylimit -l lang] | [-p problemcode] [-l language] ] [-s sleepinterval] [-b] [-n] [-c] [-r] [-d] [-v]\n", argv[0]); 
		exit(EXIT_FAILURE);
	}
	
	Logs::OpenLogFile();
	Logs::CodeRunnerStarted();
	Logs::CloseLogFile();
	
	if(ContentParser::OneFileExecution){
		FileInfoStruct* FileInfo = &(FileInfoFetchOptions->FileInfo);
		FileHandle F(FileInfo);
		F.Action();
		return 0;
	}
	
	do{
		Logs::OpenLogFile();
		bool CurrentIteration = true;
		ContentParser *ContentVar = new ContentParser();
		//if(ContentParser->OneFileExecution) OneFileInfoPrepare();
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
		sleep(SleepInterval);
		
	}while(!RunOnce);
		
    return 0;
}
