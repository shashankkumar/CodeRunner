#include "CodeRunner.h"

void CodeRunner::CheckPrerequisites(){
	ChDir(CROptions::PATH);
	ChDir(CROptions::TestCasesPath);
	ChDir(CROptions::PATH);
	ChDir(CROptions::FilesPath);
	ChDir(CROptions::PATH);
	ChDir(CROptions::LogFilePath);
	ChDir(CROptions::PATH);
	Logs::SetLogFileName(CROptions::LogFilePath, CROptions::LogFileName);
	Logs::OpenLogFile();
	Logs::CodeRunnerStarted();
	Logs::CloseLogFile();
}

void CodeRunner::ChDir(const char* dir){
	if(chdir(dir)==-1)	{
		printf("IE ERROR Cannot change directory to %s\n", dir);
		exit(EXIT_FAILURE);
	}
}

void CodeRunner::Run(){
	CheckPrerequisites();
	
	if(CROptions::OneFileExecution){
		FileInfoStruct* FileInfo = &(CROptions::FileInfoFetchOptions->FileInfo);
		FileHandle F(FileInfo);
		F.Action();
		return;
	}
	
	do{
		Logs::OpenLogFile();
		bool CurrentIteration = true;
		ContentParser *ContentVar = new ContentParser();
		//if(ContentParser->OneFileExecution) OneFileInfoPrepare();
		if(ContentVar->FetchFileInfoList()==-1){
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
		CodeRunner::GoToSleep();
		Logs::CloseLogFile();
		
	}while(!CROptions::RunOnce);
}

void CodeRunner::GoToSleep(){
	char SleepText[50];;
	sprintf(SleepText, "Going to sleep for %d seconds.\n", SLEEPINTERVAL);
	Logs::WriteLine(SleepText);
	Logs::WriteLine("============================================================================\n");
	sleep(CROptions::SleepInterval);
}

void CodeRunner::ErrorMessage(const char* msg){
	Logs::WriteLine(msg);
	exit(EXIT_FAILURE);
}
