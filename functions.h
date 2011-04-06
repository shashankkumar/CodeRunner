using namespace std;

void ToLogs(const char* log){
	printf("%s\n",log);
	return;
}

void SeparateFileIds(string *content, int* FileIds){
	char* fileIds = new char[(*content).size() + 5];
	strcpy(fileIds, (*content).c_str());
	char* ids;
	ids = strtok(fileIds, " \n\r");
	int count;
	if(ids != NULL){
		count = atoi(ids);
		ids = strtok(NULL, " \n\r");
	}
	
	char logs[100];
	sprintf(logs, "Number of Files: %d", count);
	ToLogs(logs);
	int i=0;
	FileIds[i++] = count;
	while(ids!=NULL){
		FileIds[i] = atoi(ids);
		ids = strtok(NULL, " \n\r");
		i++;
	}
	
}
 
int NumberOfFiles(string *content){
	char* fileIds = new char[(*content).size() + 5];
	strcpy(fileIds, (*content).c_str());
	char* ids;
	ids = strtok(fileIds, " \n\r");
	
	int count;
	if(ids != NULL){
		count = atoi(ids);
		ids = strtok(NULL, " \n\r");
	}
	return count;
}
