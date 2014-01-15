#include "FileHandle.h"

FileHandle::FileHandle(FileInfoStruct* FileInfo){
	this->FileInfo = FileInfo;
	TimeUsed=0.0;
	MemoryUsed=0;
	result=true;
	detailstatus[0] = '\0';
	sprintf(FileAddr, "%s%d", FILEPATH, FileInfo->FileId);
	sprintf(FileDirAddr, "%s%d/", FILEPATH, FileInfo->FileId);
	if(strcmp(FileInfo->lang, "java")==0){
		strcpy(FileName, "Main");
	}
	else strcpy(FileName, "test");
	sprintf(FullFileAddr, "%s%s", FileDirAddr, FileName);
	Logs::OpenLogFile();
	sprintf(logs, "File Id ==> %d, Problem Id ==> %s, TimeLimit ==> %d, MemoryLimit ==> %d, Lang ==> %s", FileInfo->FileId, FileInfo->ProblemId, FileInfo->TimeLimit, FileInfo->MemoryLimit, FileInfo->lang);
	Logs::WriteLine(logs, true);
}


int FileHandle::CheckLANG(){
    if(strcmp(FileInfo->lang, "cpp")==0 && !CROptions::lang_cpp)
    {
        strcpy(status, "CE");
        strcpy(detailstatus, "You are not allowed to make submissions in C++");
        return -1;
    }
    if(strcmp(FileInfo->lang, "c")==0 && !CROptions::lang_c)
    {
        strcpy(status, "CE");
        strcpy(detailstatus, "You are not allowed to make submissions in C");
        return -1;
    }
    if(strcmp(FileInfo->lang, "java")==0 && !CROptions::lang_java)
    {
        strcpy(status, "CE");
        strcpy(detailstatus, "You are not allowed to make submissions in JAVA");
        return -1;
    }
    if(strcmp(FileInfo->lang, "php")==0 && !CROptions::lang_php)
    {
        strcpy(status, "CE");
        strcpy(detailstatus, "You are not allowed to make submissions in PHP");
        return -1;
    }
    if(strcmp(FileInfo->lang, "python")==0 && !CROptions::lang_python)
    {
        strcpy(status, "CE");
        strcpy(detailstatus, "You are not allowed to make submissions in PYTHON");
        return -1;
    }
    if(strcmp(FileInfo->lang, "pascal")==0 && !CROptions::lang_pascal)
    {
        strcpy(status, "CE");
        strcpy(detailstatus, "You are not allowed to make submissions in PASCAL");
        return -1;
    }
    if(strcmp(FileInfo->lang, "perl")==0 && !CROptions::lang_perl)
    {
        strcpy(status, "CE");
        strcpy(detailstatus, "You are not allowed to make submissions in PERL");
        return -1;
    }
    return 0;
}


int FileHandle::FetchFile(){
	if(!CROptions::DownloadSourceFile) {
		return 0;
	}
	if(FTPON) {
		int res = FileCurl.GetFileFromFTP(FileInfo->FileId);
		if(res==-1)	{
			strcpy(status, "IE");
			sprintf(detailstatus, "Failure to download source code.");
			return -1;
		}
	}
	else if(HTTPON){
		int res = FileCurl.GetFileFromHTTP(FileInfo->FileId);
		if(res==-1){
			strcpy(status, "IE");
			sprintf(detailstatus, "Failure to download source code.");
			return -1;
		}
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
	//printf("%s\n",command );
	if ( !(fpipe = (FILE*)popen(command,"r")) ){
	// If fpipe is NULL
		perror("Problems with pipe");
		Logs::WriteLine("Problems with pipe");
		return -1;
	}
	else {
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
		}
	}
	pclose(fpipe);
	return 0;
}

int FileHandle::MakeDir(){
	int ErrNo;

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
	if(strcmp(FileInfo->lang, "python")==0) sprintf(systemString, "cp %s.txt %s.py", FileAddr, FullFileAddr);
	else if(strcmp(FileInfo->lang, "pascal")==0) sprintf(systemString, "cp %s.txt %s.p", FileAddr, FullFileAddr);
	else if(strcmp(FileInfo->lang, "php")==0) sprintf(systemString, "cp %s.txt %s.php", FileAddr, FullFileAddr);
	else if(strcmp(FileInfo->lang, "perl")==0) sprintf(systemString, "cp %s.txt %s.pl", FileAddr, FullFileAddr);
	else sprintf(systemString, "cp %s.txt %s.%s", FileAddr, FullFileAddr, FileInfo->lang);
	if(system(systemString)==-1){
		strcpy(status, "IE");
		strcpy(detailstatus, "Error in copying dowloaded file.");
		return -1;
	}
	return 0;
}

void FileHandle::Compile(){
	pipeCompile();
	/*
	if(CompileOutput.length()!=0){
		Logs::WriteLine("Unsuccessful");
		result = false;
		strcpy(status, "CE");

		if(strlen(CompileOutput.c_str())<=10000) strcpy(detailstatus, CompileOutput.c_str());
	}
	else Logs::WriteLine("Successful\n");
	*/
	if(result) Logs::WriteLine("Successful\n");
}

void FileHandle::pipeCompile(){
	FILE *fpipe;
    if(strcmp(FileInfo->lang, "cpp")==0)
    	sprintf(command, "g++ -w -static %s.cpp -o %s 2>&1", FullFileAddr, FullFileAddr);
    else if(strcmp(FileInfo->lang, "c") == 0)
    	sprintf(command, "gcc -w -static %s.c -o %s 2>&1", FullFileAddr, FullFileAddr);
    else if(strcmp(FileInfo->lang, "java")==0)
		sprintf(command, "javac %s.java", FullFileAddr);
	else if(strcmp(FileInfo->lang, "python")==0)
		sprintf(command, "python -m py_compile %s.py", FullFileAddr);
	else if(strcmp(FileInfo->lang, "pascal")==0)
		sprintf(command, "fpc %s.p", FullFileAddr);
	else if(strcmp(FileInfo->lang, "perl")==0)
		sprintf(command, "perl -c %s.pl", FullFileAddr);
	else if(strcmp(FileInfo->lang, "php")==0)
		sprintf(command, "php -l %s.php", FullFileAddr);


	Logs::Write("\nCompiling file ==>  ");
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
	int compilestatus = pclose(fpipe);
	if(compilestatus!=0){
		strcpy(status, "CE");
		if(strlen(CompileOutput.c_str())<10000) strcpy(detailstatus, CompileOutput.c_str());
		result = false;
		//printf(" Compile length %d \n", (int)strlen(detailstatus));
	}
	//printf("compile status - %d\n", compilestatus);
}

int FileHandle::pipeNoOfTestCases(){
    FILE *fpipe;
    char line[256];
    int TestCaseNo;
    sprintf(command, "ls %s%s/Input/ -l | egrep -c '^-'", TESTCASESPATH, FileInfo->ProblemId);

	if ( !(fpipe = (FILE*)popen(command,"r")) ){
	// If fpipe is NULL
		perror("Problems with pipe");
		Logs::WriteLine("Problems with pipe");
		return -1;
	}
	else{
		if ( fgets( line, sizeof line, fpipe)){
			TestCaseNo = atoi(line);
		}
	}
	pclose(fpipe);
	return TestCaseNo;
}

int FileHandle::PrepareToExecute(){
	sprintf(systemString, "cp %s%s/Input/* %s", TESTCASESPATH, FileInfo->ProblemId, FileDirAddr);
	system(systemString);

	NoOfTestCases = pipeNoOfTestCases();
	if(NoOfTestCases == 0){
		strcpy(status, "IE");
		strcpy(detailstatus, "No Test Case file specified.");
		return -1;
	}
	else if(NoOfTestCases == -1){
		strcpy(status, "IE");
		strcpy(detailstatus, "Problem in determining number of test case files.");
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

	for( TestCaseId = 1; (result==true && TestCaseId<=NoOfTestCases); TestCaseId++ ){

		PipeExecute();
		sprintf(str, "\nTest Case %d\n%s", TestCaseId, ExecutionStr.c_str());
		Logs::Write(str);

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

		//TimeUsed += TestCaseExecutionTime;
		if(TestCaseExecutionTime>TimeUsed){
			TimeUsed=TestCaseExecutionTime;
		}
		MemoryUsed = max(MemoryUsed, TestCaseExecutionMemory);
		if( TimeUsed > (float) FileInfo->TimeLimit){
			result = false; sprintf(status, "TLE");
		}

		if(result==false) break;

		MatchOutput();
		if(result==false){
			sprintf(logs, "Output Matching: WA");
			Logs::WriteLine(logs);
			strcpy(status,"WA");
			break;
		}
		else{
			sprintf(logs, "Output Matching: AC");
			Logs::WriteLine(logs);
		}
	}

	Logs::WriteLine("");
	if(result==true) Logs::WriteLine("Execution ==> Successful");
	else Logs::WriteLine("Execution ==> Failed");

	/*
	if(result==true) Logs::WriteLine("\nMatching Output... ");
	for(TestCaseId=1; (result==true && TestCaseId<=NoOfTestCases); TestCaseId++){
		MatchOutput();
		if(result==false){
			sprintf(logs, "Failed on test case %d", TestCaseId);
			Logs::WriteLine(logs);
			strcpy(status,"WA");
		}
	}
	if(result==true) Logs::WriteLine("All output successfully matched.");
	Logs::WriteLine("");
	*/
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

	sprintf(command, "diff %s %s --ignore-all-space --ignore-blank-lines --ignore-tab-expansion --ignore-space-change --brief 2>&1", FromFileStr, ToFileStr);
	//printf("%s\n", command);
	pipeMatch();
}

void FileHandle::SendResults(){
	sprintf(timeused, "%0.3f", TimeUsed);
	sprintf(memoryused, "%d", MemoryUsed);
	sprintf(fileid, "%d", FileInfo->FileId);
	sprintf(logs, "FileId ==> %s Status==>%s DetailStatus==>%s TimeUsed==>%s MemoryUsed==>%s Language==>%s", fileid, status, detailstatus, timeused, memoryused, FileInfo->lang);
	Logs::WriteLine(logs, true);


	if(CROptions::SendResults) FileCurl.SendResultsToWebpage(fileid, status, detailstatus, timeused, memoryused);
	Logs::WriteLine("\n================================================================================\n");

}

void FileHandle::CleanUp(){
	//Delete directory as well source files
	sprintf(systemString, "rm -rf %s", FileAddr);
	system(systemString);
	sprintf(systemString, "rm -f %s.txt", FileAddr);
	system(systemString);
}

void FileHandle::FileOperations(){

	if(CheckLANG() == -1 || FetchFile() == -1 || CheckMIME() == -1) return;
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
	if(CROptions::Clean)
		CleanUp();
}
