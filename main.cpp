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
#include "headers.h"
#include "CROptions.h"
#include "CodeRunner.h"

int main(int argc, char* argv[])
{
	CodeRunner::ChDir(CROptions::PATH);
	
	int opt;
	bool DownloadSourceFile = true;
	bool UsageError = false;
	while((opt = getopt(argc, argv, "abcdf:l:m:np:qr:s:t:v")) != -1){
		switch(opt){
			// For fetching all file-ids irrespective of evaluation status.
			case 'a':
				CROptions::GetAllFileIds = true;
			break;
			// For sending results and forcing insertion of those results.
			case 'b':
				CROptions::ForcePushResult = true;
			break;
			// For clearing Files directory after execution of source code.
			case 'c':
				CROptions::Clean = true;
			break;
			// For not downloading source codes. In such a case, the source codes
			// should already be present in the Files directory.
			case 'd':
				CROptions::DownloadSourceFile = false;
			break;
			// For pre-defining FileId
			case 'f':
				CROptions::FileInfoFetchOptions->FileId_Predefined = true;
				CROptions::FileInfoFetchOptions->FileInfo.FileId = atoi(optarg);
			break;
			case 'i':
				CROptions::OneFileExecution = true;
			break;
			// For pre-defining Language
			case 'l':
				CROptions::FileInfoFetchOptions->Lang_Predefined = true;
				strcpy(CROptions::FileInfoFetchOptions->FileInfo.lang, optarg);
			break;
			// For specifying pre-defined memory limit.
			case 'm':
				CROptions::FileInfoFetchOptions->MemoryLimit_Predefined = true;
				CROptions::FileInfoFetchOptions->FileInfo.MemoryLimit = atoi(optarg);
			break;
			// For not sending results after evaluation.
			case 'n':
				CROptions::SendResults = false;
			break;
			// For pre-defining ProblemId
			case 'p':
				CROptions::FileInfoFetchOptions->ProblemId_Predefined = true;
				strcpy(CROptions::FileInfoFetchOptions->FileInfo.ProblemId, optarg);
			break;
			case 'q':
				CROptions::PrintOnScreen = false;
			break;
			// For setting CodeRunner to just run for one epoch.
			case 'r':
				CROptions::RunOnce = true;
			break;
			// For specifying Sleep Interval after each epoch.
			case 's':
				CROptions::SleepInterval = atoi(optarg);
			break;
			// For specifying pre-defined time-limit.
			case 't':
				CROptions::FileInfoFetchOptions->TimeLimit_Predefined = true;
				CROptions::FileInfoFetchOptions->FileInfo.TimeLimit = atoi(optarg);
			break;
			// For printing version related information.
			case 'v':
				;
			break;
			// For no printing on screen. Running CodeRunner in "quiet" option.
			default: /* '?' */
				UsageError = true;
		}
	}

	if(CROptions::FileInfoFetchOptions->FileId_Predefined){
		if(CROptions::OneFileExecution){ 
			if(!(CROptions::FileInfoFetchOptions->MemoryLimit_Predefined && CROptions::FileInfoFetchOptions->TimeLimit_Predefined && 
			CROptions::FileInfoFetchOptions->ProblemId_Predefined && CROptions::FileInfoFetchOptions->Lang_Predefined)) UsageError = true;
		}
	}
	else if(CROptions::FileInfoFetchOptions->ProblemId_Predefined || CROptions::FileInfoFetchOptions->Lang_Predefined) UsageError = true;
	
	if(UsageError){
		fprintf(stderr, "Usage: %s [-f fileid [-i -p problemcode -t timelimit -m memorylimit -l lang] | [-p problemcode] [-l language] ] [-s sleepinterval] [-a] [-b] [-n] [-c] [-r] [-d] [-v]\n", argv[0]); 
		exit(EXIT_FAILURE);
	}
	
	CodeRunner::CheckPrerequisites();
	CodeRunner::Run();
    return 0;
}
