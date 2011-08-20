#include "FileHandle.h"

FileHandle::FileHandle(int FileId, const char* pid, int tl, int ml, const char* language){
	this->FileId = FileId;
	TimeLimit = tl;
	MemoryLimit = ml;
	TimeUsed=0.0;
	MemoryUsed=0;
	ProblemId = pid;
	lang = language;
	result=true;
	sprintf(detailstatus,"\0");
	Logs::OpenLogFile();
	sprintf(logs, "Beginning operations on File Id ==> %d\n", FileId);
	Logs::WriteLine(logs, true);
	sprintf(logs, "File Id ==> %d, Problem Id ==> %s, TimeLimit ==> %d, MemoryLimit ==> %d, Lang ==> %s", FileId, ProblemId, TimeLimit, MemoryLimit, lang);
	Logs::WriteLine(logs);
}

int FileHandle::FetchFile(){
	if(FTPON) {
		int res = FileCurl.GetFileFromFTP(FileId);
		if(res==-1)	return -1;
	}
	else if(HTTPON){
		int res = FileCurl.GetFileFromHTTP(FileId);
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
    sprintf(command, "file -b --mime-type %s%d.txt", FILEPATH, FileId);
	
	if ( !(fpipe = (FILE*)popen(command,"r")) ){  
	// If fpipe is NULL
		perror("Problems with pipe");
		Logs::WriteLine("Problems with pipe");
		return -1;
	}
	else{
		if ( fgets( line, sizeof line, fpipe)){
			printf("\n%s\n", line);
			if(strncmp(line, "text", 4) != 0){
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
	sprintf(dirString, "%s%d",FILEPATH, FileId);
	Logs::WriteLine("Creating directory.");
	if( mkdir(dirString, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH)==-1){
		ErrNo=errno;
		if(ErrNo==17) Logs::WriteLine("Directory already created.. Continuing");
		else {
			strcpy(status, "IE");
			sprintf(detailstatus, "Failure to create directory for file operations. Error Number: %d", errno);
			return -1;
		}
	}
	sprintf(systemString, "cp %s%d.txt %s%d/main.%s", FILEPATH, FileId, FILEPATH, FileId, lang);
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
		strcpy(detailstatus, CompileOutput.c_str());
	}
	else Logs::WriteLine("Successful\n");
}

void FileHandle::pipeCompile(){
	FILE *fpipe;
    if(strcmp(lang, "cpp")==0)
    	sprintf(command, "g++ -w -static %s%d/main.cpp -o %s%d/main 2>&1", FILEPATH, FileId, FILEPATH, FileId);
    else if(strcmp(lang, "c") == 0)
    	sprintf(command, "g++ -w -static %s%d/main.c -o %s%d/main 2>&1", FILEPATH, FileId, FILEPATH, FileId);
    else if(strcmp(lang, "java")==0)
		sprintf(command, "javac -nowarn -deprecation %s%d/main.java  2>&1", FILEPATH, FileId);    	
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
    sprintf(command, "ls %s%s/Input/ -l | egrep -c '^-'", TESTCASESPATH, ProblemId);
	
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
	sprintf(systemString, "cp %s%s/Input/* %s%d/", TESTCASESPATH, ProblemId, FILEPATH, FileId);
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
    if(strcmp(lang,"cpp")==0 || strcmp(lang,"c")==0){
    	sprintf(command, "./Execution %d %d %d %d %s", FileId, TestCaseId, TimeLimit, MemoryLimit, lang);
    }
    else if(strcmp(lang, "java")==0){
    	sprintf(command, "./java_Execution %d %d %d %d %s", FileId, TestCaseId, TimeLimit, MemoryLimit, lang);
    }
    
   	char line[1024];

	if ( !(fpipe = (FILE*)popen(command,"r")) ){  
	// If fpipe is NULL
		perror("Problems with pipe");
		Logs::WriteLine("Problems with pipe");
	}
	else{
		while ( fgets( line, sizeof line, fpipe)){
			ExecutionStr.append(line, strlen(line));
		}
	}
	pclose(fpipe);
}
	
void FileHandle::Execute(){
	
	Logs::WriteLine("Beginning Execution...");
	
	for( TestCaseId = 1; TestCaseId <= NoOfTestCases; TestCaseId++ ){

		PipeExecute();
		strcpy(str, ExecutionStr.c_str());
		token = strtok(str, " \n");
		strcpy(status, token);
		if(strcmp(token, "AC")!=0) result=false;
		if(strcmp(token, "RE")==0 || strcmp(token, "IE")==0 ){
			token = strtok(NULL, "\n");
			strcpy(detailstatus, token);
		}
		token = strtok(NULL, " \n"); sprintf(TestCaseExecutionTime, "%s", token);
		TimeUsed += (float) atof( TestCaseExecutionTime );
		if( TimeUsed > (float) TimeLimit){
			result = false;
			sprintf(status, "TLE");
			sprintf(detailstatus, "\0");
		}
		
		sprintf(logs, "%d ==> %s %s %s", TestCaseId, status, detailstatus, TestCaseExecutionTime);
		Logs::Write(logs);
		if(result==false){
			break;
		}
	}
	
	if(result==true) Logs::WriteLine("Execution ==> Successful");
	else Logs::WriteLine("Execution ==> Failed");
	Logs::WriteLine("Matching Output... ");
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
	sprintf(FromFileStr, "%s%s/Output/%d.txt", TESTCASESPATH, ProblemId, TestCaseId);
	sprintf(ToFileStr, "%s%d/%do.txt", FILEPATH, FileId, TestCaseId);
	char cmd[100];
	sprintf(command, "diff %s %s --ignore-all-space --ignore-blank-lines --ignore-tab-expansion --ignore-space-change --brief 2>&1", FromFileStr, ToFileStr);
	pipeMatch();
}

void FileHandle::SendResults(){
	sprintf(timeused, "%0.3f", TimeUsed);
	sprintf(memoryused, "%d", MemoryUsed);
	sprintf(fileid, "%d", FileId);
	sprintf(logs, "FileId ==> %s\n Status==>%s DetailStatus==>%s TimeUsed==>%s MemoryUsed==>%s", fileid, status, detailstatus, timeused, memoryused); 
	Logs::WriteLine(logs, true);
	FileCurl.SendResultsToWebpage(fileid, status, detailstatus, timeused, memoryused);

	Logs::WriteLine("\n================================================================================\n");
}
	
void FileHandle::CleanUp(){
	sprintf(systemString, "rm -rf %s%d", FILEPATH, FileId);
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
	;//CleanUp();
}
