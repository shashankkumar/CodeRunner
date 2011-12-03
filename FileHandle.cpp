#include "FileHandle.h"

FileHandle::FileHandle(FileInfoStruct* FileInfo){
	this->FileInfo = FileInfo;
	TimeUsed=0.0;
	MemoryUsed=0;
	result=true;
	sprintf(detailstatus,"\0");
	sprintf(FileAddr, "%s%d", FILEPATH, FileInfo->FileId);
	sprintf(FileDirAddr, "%s%d/", FILEPATH, FileInfo->FileId);
	if(strcmp(FileInfo->lang, "java")){
		strcpy(FileName, "Main");
	}
	else strcpy(FileName, "test");
	sprintf(FullFileAddr, "%s%s", FileDirAddr, FileName);
	Logs::OpenLogFile();
	sprintf(logs, "Beginning operations on File Id ==> %d\n", FileInfo->FileId);
	Logs::WriteLine(logs, true);
	sprintf(logs, "File Id ==> %d, Problem Id ==> %s, TimeLimit ==> %d, MemoryLimit ==> %d, Lang ==> %s", FileInfo->FileId, FileInfo->ProblemId, FileInfo->TimeLimit, FileInfo->MemoryLimit, FileInfo->lang);
	Logs::WriteLine(logs);
}

int FileHandle::FetchFile(){
	if(!DownloadSourceFile) {
		
		return 0;
	}
	if(FTPON) {
		int res = FileCurl.GetFileFromFTP(FileInfo->FileId);
		if(res==-1)	return -1;
	}
	else if(HTTPON){
		int res = FileCurl.GetFileFromHTTP(FileInfo->FileId);
		if(res==-1)	return -1;
	}
	else {
		strcpy(status, "IE");
		strcpy(detailstatus, "Cannot download source file. No method specified for downloading!!!");
		return -1;
	}
	return 0;
}

int FileHandle::CheckMIME(){
	FILE *fpipe;
    char line[256];
    sprintf(command, "file -b --mime-type %s.txt", FileAddr);
	
	if ( !(fpipe = (FILE*)popen(command,"r")) ){  
	// If fpipe is NULL
		perror("Problems with pipe");
		Logs::WriteLine("Problems with pipe");
		return -1;
	}
	else{
		if ( fgets( line, sizeof line, fpipe)){
			printf("mime-type -> %s", line);
			
			if(strncmp(line+12, "x-empty", 7)==0){
				result = false;
				strcpy(status, "CE");
				strcpy(detailstatus, "You have submitted an empty file!");
			}
			
			else if(strncmp(line, "text", 4) != 0){
				result = false;
				strcpy(status, "CE");
				strcpy(detailstatus, "The source file is not a text file. Failed MIME check test.");
			}
			return 0;
		}
	}
	pclose(fpipe);
}

int FileHandle::MakeDir(){
	int ErrNo;
	char dirString[100];
	Logs::WriteLine("Creating directory.");
	if( mkdir(FileDirAddr, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH)==-1){
		ErrNo=errno;
		if(ErrNo==17) Logs::WriteLine("Directory already created.. Continuing");
		else {
			strcpy(status, "IE");
			sprintf(detailstatus, "Failure to create directory for file operations. Error Number: %d", errno);
			return -1;
		}
	}
	sprintf(systemString, "cp %s.txt %s.%s", FileAddr, FullFileAddr, FileInfo->lang);
	if(system(systemString)==-1){
		strcpy(status, "IE");
		strcpy(detailstatus, "Error in copying dowloaded file.");
		return -1;
	}
	return 0;
}

void FileHandle::Compile(){
	pipeCompile();
	if(CompileOutput.length()!=0){
		Logs::WriteLine("Unsuccessful"); 
		result = false;
		strcpy(status, "CE");
		
		if(strlen(CompileOutput.c_str())<=500) strcpy(detailstatus, CompileOutput.c_str());
		printf("%d %d\n", (int)strlen(CompileOutput.c_str()), (int)strlen(detailstatus));
	}
	else Logs::WriteLine("Successful\n");
}

void FileHandle::pipeCompile(){
	FILE *fpipe;
    if(strcmp(FileInfo->lang, "cpp")==0)
    	sprintf(command, "g++ -w -static %s.cpp -o %s 2>&1", FullFileAddr, FullFileAddr);
    else if(strcmp(FileInfo->lang, "c") == 0)
    	sprintf(command, "gcc -w -static %s.c -o %s 2>&1", FullFileAddr, FullFileAddr);
    else if(strcmp(FileInfo->lang, "java")==0)
		sprintf(command, "javac -nowarn -deprecation %s.java  2>&1", FullFileAddr);    	
    Logs::Write("Compiling file ==>  ");
	char line[256];
	
	if ( !(fpipe = (FILE*)popen(command,"r")) ){  
		perror("Problems with pipe");
		Logs::WriteLine("Problems with pipe");
	}
	else{
		while ( fgets( line, sizeof line, fpipe)){
			CompileOutput.append(line, strlen(line));
		}
	}
	pclose(fpipe);
}

int FileHandle::pipeNoOfTestCases(){
    FILE *fpipe;
    char line[256];
    sprintf(command, "ls %s%s/Input/ -l | egrep -c '^-'", TESTCASESPATH, FileInfo->ProblemId);
	
	if ( !(fpipe = (FILE*)popen(command,"r")) ){  
	// If fpipe is NULL
		perror("Problems with pipe");
		Logs::WriteLine("Problems with pipe");
		return -1;
	}
	else{
		while ( fgets( line, sizeof line, fpipe)){
			return atoi(line);
		}
	}
	pclose(fpipe);
}

int FileHandle::PrepareToExecute(){
	sprintf(systemString, "cp %s%s/Input/* %s", TESTCASESPATH, FileInfo->ProblemId, FileDirAddr);
	system(systemString);
	
	NoOfTestCases = pipeNoOfTestCases();
	if(NoOfTestCases==0){
		strcpy(status, "IE");
		strcpy(detailstatus, "No Test Case file specified.");
		return -1;
	}
	sprintf(systemString, "Number of Test Cases = %d",NoOfTestCases);
	Logs::WriteLine(systemString);
	return 0;
}
	
void FileHandle::PipeExecute(){
	FILE *fpipe;
	int MemoryLimitInKb = FileInfo->MemoryLimit * 1024;
	sprintf(command, "./Execution %d %s %d %d %d %s", FileInfo->FileId, FileName, TestCaseId, FileInfo->TimeLimit, MemoryLimitInKb, FileInfo->lang);
    
   	char line[1024];

	if ( !(fpipe = (FILE*)popen(command,"r")) ){  
	// If fpipe is NULL
		perror("Problems with pipe");
		Logs::WriteLine("Problems with pipe");
	}
	else{
		ExecutionStr.clear();
		while ( fgets( line, sizeof line, fpipe)){
			ExecutionStr.append(line, strlen(line));
		}
	}
	pclose(fpipe);
}
	
void FileHandle::Execute(){
	
	Logs::WriteLine("Beginning Execution... ");
	
	for( TestCaseId = 1; TestCaseId <= NoOfTestCases; TestCaseId++ ){

		PipeExecute();
		strcpy(str, ExecutionStr.c_str());
		printf("\n%s\n", str);
		char* ptr = strstr(str, "status");
		if(ptr!=NULL){
			sscanf(ptr, "%*s %s", status);
			if(strcmp(status, "AC")!=0) result=false;
			if(strcmp(status, "RE")==0){
				ptr = strstr(ptr, "detailstatus");
				if(ptr!=NULL) sscanf(ptr, "%*s %s", detailstatus);
			}
			else if(strcmp(status, "IE")==0){
				ptr = strstr(ptr, "detailstatus");
				if(ptr!=NULL){
					char* ixspace = strchr(ptr, ' ');
					char* ixnewline = strchr(ptr, '\n');
					memcpy(detailstatus, ixspace, ixnewline-ixspace);
					detailstatus[ixnewline-ixspace+1]='\0';
				}
			}
			ptr = strstr(str, "timeused");
			if(ptr!=NULL) sscanf(ptr, "%*s %f", &TestCaseExecutionTime);
			ptr = strstr(str, "memoryused");
			if(ptr!=NULL) sscanf(ptr, "%*s %d", &TestCaseExecutionMemory);
		}
		
		/*
		token = strtok(str, " \n");
		strcpy(status, token);
		if(strcmp(token, "AC")!=0) result=false;
		if(strcmp(token, "RE")==0 || strcmp(token, "IE")==0 ){
			token = strtok(NULL, "\n");
			strcpy(detailstatus, token);
		}
		token = strtok(NULL, " \n"); sprintf(TestCaseExecutionTime, "%s", token);
		token = strtok(NULL, " \n"); sprintf(TestCaseExecutionMemory, "%s", token);
		*/
		TimeUsed += TestCaseExecutionTime;
		MemoryUsed = max(MemoryUsed, TestCaseExecutionMemory);
		printf("time - %f \n", TimeUsed);
		if( TimeUsed > (float) FileInfo->TimeLimit){
			result = false;
			sprintf(status, "TLE");
			sprintf(detailstatus, "\0");
		}
		
		sprintf(logs, "%d ==> %s %s %f %d\n", TestCaseId, status, detailstatus, TestCaseExecutionTime, TestCaseExecutionMemory);
		Logs::Write(logs);
		if(result==false){
			break;
		}
	}
	
	if(result==true) Logs::WriteLine("Execution ==> Successful");
	else Logs::WriteLine("Execution ==> Failed");
	
	if(result==true) Logs::WriteLine("Matching Output... ");
	for(TestCaseId=1; (result==true && TestCaseId<=NoOfTestCases); TestCaseId++){
		MatchOutput();
		if(result==false){
			sprintf(logs, "Failed on test case %d", TestCaseId);
			Logs::WriteLine(logs);	
			strcpy(status,"WA");
		}
	}
}
	
void FileHandle::pipeMatch(){
    FILE *fpipe;
    char line[256];
    
	if ( !(fpipe = (FILE*)popen(command,"r")) ){  
	// If fpipe is NULL
		perror("Problems with pipe");
		Logs::WriteLine("Problems with pipe");
	}
	else{
		while ( fgets( line, sizeof line, fpipe)){
			result = false;
		}
	}
	pclose(fpipe);
}

void FileHandle::MatchOutput(){
	char FromFileStr[100], ToFileStr[100];
	sprintf(FromFileStr, "%s%s/Output/%d.txt", TESTCASESPATH, FileInfo->ProblemId, TestCaseId);
	sprintf(ToFileStr, "%s%do.txt", FileDirAddr, TestCaseId);
	char cmd[1000];
	sprintf(command, "diff %s %s --ignore-all-space --ignore-blank-lines --ignore-tab-expansion --ignore-space-change --brief 2>&1", FromFileStr, ToFileStr);
	printf("%s\n", command);
	pipeMatch();
}

void FileHandle::SendResults(){
	sprintf(timeused, "%0.3f", TimeUsed);
	sprintf(memoryused, "%d", MemoryUsed);
	sprintf(fileid, "%d", FileInfo->FileId);
	sprintf(logs, "FileId ==> %s Status==>%s DetailStatus==>%s TimeUsed==>%s MemoryUsed==>%s", fileid, status, detailstatus, timeused, memoryused); 
	Logs::WriteLine(logs, true);
	if(SendResultsVar) FileCurl.SendResultsToWebpage(fileid, status, detailstatus, timeused, memoryused);

	Logs::WriteLine("\n================================================================================\n");
}
	
void FileHandle::CleanUp(){
	sprintf(systemString, "rm -rf %s", FileAddr);
	system(systemString);
}

void FileHandle::FileOperations(){

	if(FetchFile() == -1) return;
	if(CheckMIME() == -1) return;
	if(result==false) return;
	if(MakeDir()==-1) return;

	Compile();
	
	if(result==false){
		CleanUp();
		return;
	}

	if(PrepareToExecute()==-1){
		CleanUp();
		return;
	}

	Execute();

}

bool FileHandle::getResult(){
	return result;
}

void FileHandle::Action(){
	FileOperations();
	SendResults();
}

FileHandle::~FileHandle(){
	if(Clean) CleanUp();
}

bool FileHandle::Clean=false;
bool FileHandle::SendResultsVar=true;
bool FileHandle::DownloadSourceFile = true;
