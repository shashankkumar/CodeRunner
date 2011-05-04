void FileThread(int FileId, const char* ProblemId, int TimeLimit, int MemoryLimit, const char* lang){
	
	FileHandle *F = new FileHandle(FileId, ProblemId, lang);
	
	if(F->FetchFile()==-1) return;
	if(F->MakeDir()==-1) return;
	
	F->Compile();
	
	if(F->result==true){
		if(F->PrepareToExecute()==-1){
			F->CleanUp();
			return;
		}
		F->Execution(TimeLimit, MemoryLimit);
	}
	F->SendResults();
	//F->CleanUp();
	delete F;
}

