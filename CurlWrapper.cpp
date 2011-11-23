#include "CurlWrapper.h"

size_t CurlWrapper::ContentInVar(void* ptr, size_t size, size_t nmemb, string *stream){
	stream -> append((char *)ptr, size * nmemb);
	return size*nmemb;
}

size_t CurlWrapper::ContentInFileHTTP(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

size_t CurlWrapper::ContentInFileFTP(void *buffer, size_t size, size_t nmemb, void *stream){
	struct FtpFile *out=(struct FtpFile *)stream;
	if(out && !out->stream) {
    	/* open file for writing */ 
   		out->stream=fopen(out->filename, "wb");
    	if(!out->stream)
   			return -1; /* failure, can't open file to write */ 
		}
	return fwrite(buffer, size, nmemb, out->stream);
}

int CurlWrapper::GetFileFromFTP(int FileId){
	curl = curl_easy_init();
	
	//string URL, FileName, SavedFileName;
	//URL = strcpy( URL_c );
	//FileName = strcpy ( 
	char FTPFileURL[100], SavedFileName[100];
	sprintf(FTPFileURL, "%s%d.txt", FTPADDRESS, FileId);
	sprintf(SavedFileName, "%s%d.txt", FILEPATH, FileId);
	struct FtpFile ftpfile={
   		SavedFileName, /* name to store the file as if succesful */ 
   		NULL
	};
  		
	if(curl) {
   		
   		curl_easy_setopt(curl, CURLOPT_URL, FTPFileURL);
	    /* Define our callback to get called when there's data to be written */ 
   		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ContentInFileFTP);
   		/* Set a pointer to our struct to pass to the callback */ 
   		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
   		#ifdef FTPUSERNAME
   			curl_easy_setopt(curl, CURLOPT_USERNAME, FTPUSERNAME);
   		#endif
   		#ifdef FTPPASSWORD
   			curl_easy_setopt(curl, CURLOPT_PASSWORD, FTPPASSWORD);
   		#endif
 	
	    /* Switch on full protocol/debug output */ 
	    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	 
	    res = curl_easy_perform(curl);
	    curl_easy_cleanup(curl);
	    if(CURLE_OK != res) {
	       	sprintf(logs, "Failure to fetch file using FTP request. Curl Error code: %d\n", res);
   			Logs::WriteLine(logs);
	    	return -1;
	    }
	}
	sprintf(logs, "File fetched successfully through FTP request.");
	Logs::WriteLine(logs);
	return 0;
}
	
int CurlWrapper::GetFileFromHTTP(int FileId){
		
	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect: ";
	
	char FILEID[10];
	sprintf(FILEID,"%d", FileId);
	
	/* Fill in the POST fields */ 
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "username", CURLFORM_COPYCONTENTS, USERNAME, CURLFORM_END);
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "password", CURLFORM_COPYCONTENTS, PASSWORD, CURLFORM_END);
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "fileid", CURLFORM_COPYCONTENTS, FILEID, CURLFORM_END);
	
	FILE *fp;
   	char SavedFileName[FILENAME_MAX];
   	sprintf(SavedFileName, "%s%d.txt", FILEPATH, FileId);
   	curl = curl_easy_init();
   	headerlist = curl_slist_append(headerlist, buf);
	if (curl) {
       	fp = fopen(SavedFileName,"wb");
   		curl_easy_setopt(curl, CURLOPT_URL, HTTPADDRESS);
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ContentInFileHTTP);
   	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
   	    res = curl_easy_perform(curl);
   	    curl_easy_cleanup(curl);
   	    curl_formfree(formpost);
		/* free slist */ 
    	curl_slist_free_all (headerlist);
   		fclose(fp);
   		
   		if(CURLE_OK!=res){
   			Logs::WriteLine("Failure to fetch file through HTTP request...");
   			return -1;
   		}
   		else{
   			Logs::WriteLine("File fetched successfully through HTTP request...");
   			return 0;
   		}
   	}
   	return -1;
}
	
int CurlWrapper::FetchContentFromWebPage(FileInfoFetchOptionsStruct* FileInfoFetchOptions, string *content){
		
	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect: ";
	
	/* Fill in the POST fields */ 
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "username", CURLFORM_COPYCONTENTS, USERNAME, CURLFORM_END);
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "password", CURLFORM_COPYCONTENTS, PASSWORD, CURLFORM_END);
	
	char optstr[11];
	if(FileInfoFetchOptions->f){
		sprintf(optstr, "%d", FileInfoFetchOptions->FileInfo.FileId);
		curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "fileid", CURLFORM_COPYCONTENTS, optstr, CURLFORM_END);
	}
	
	if(FileInfoFetchOptions->p){
		sprintf(optstr, "%s", FileInfoFetchOptions->FileInfo.ProblemId);
		curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "problemid", CURLFORM_COPYCONTENTS, optstr, CURLFORM_END);
	}
	
	if(FileInfoFetchOptions->l){
		sprintf(optstr, "%s", FileInfoFetchOptions->FileInfo.lang);
		curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "lang", CURLFORM_COPYCONTENTS, optstr, CURLFORM_END);
	}
		
	curl = curl_easy_init();
	/* initalize custom header list (stating that Expect: 100-continue is not wanted */ 
	headerlist = curl_slist_append(headerlist, buf);
	if(curl) {
    	/* what URL that receives this POST */ 
    	curl_easy_setopt(curl, CURLOPT_URL, URLToGetFileIds);
    
    	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ContentInVar);
    	string buffer;
    	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    	res = curl_easy_perform(curl);
    	
    	(*content) = buffer;
    	
    	/* always cleanup */ 
    	curl_easy_cleanup(curl);
   		/* then cleanup the formpost chain */ 
    	curl_formfree(formpost);
		/* free slist */ 
    	curl_slist_free_all (headerlist);
   		if(CURLE_OK!=res){
   			sprintf(logs, "Failure to fetch File Ids. Curl Error code: %d", res);
   			Logs::WriteLine(logs, true);
   			return -1;
   		}
   		else{
   			sprintf(logs, "File Ids fetched succesfully.");
   			Logs::WriteLine(logs, true);
			Logs::WriteLine(buffer.c_str());
   			return 0;
   		}
  	}
  	return -1;		// Control should not reach here in normal circumstances
}

void CurlWrapper::SendResultsToWebpage(const char* fileid, const char* status, const char* detailstatus, const char* time, const char* memory){
		
	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect: ";
	
	curl_global_init(CURL_GLOBAL_ALL);

	/* Fill in the POST fields */ 
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "username", CURLFORM_COPYCONTENTS, USERNAME, CURLFORM_END);
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "password", CURLFORM_COPYCONTENTS, PASSWORD, CURLFORM_END);
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "fileid", CURLFORM_COPYCONTENTS, fileid, CURLFORM_END);
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "status", CURLFORM_COPYCONTENTS, status, CURLFORM_END);
	//printf("%s\n", detailstatus);
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "detailstatus", CURLFORM_COPYCONTENTS, detailstatus, CURLFORM_END);
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "time", CURLFORM_COPYCONTENTS, time, CURLFORM_END);
	curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "memory", CURLFORM_COPYCONTENTS, memory, CURLFORM_END);
	if(ForcePushResult) 
		curl_formadd( &formpost, &lastptr, CURLFORM_COPYNAME, "force", CURLFORM_COPYCONTENTS, "true", CURLFORM_END);
	
	curl = curl_easy_init();
	/* initalize custom header list (stating that Expect: 100-continue is not wanted */ 
	headerlist = curl_slist_append(headerlist, buf);
	if(curl) {
    	/* what URL that receives this POST */ 
    	curl_easy_setopt(curl, CURLOPT_URL, URLToSendResults);
    	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ContentInVar);
    	string buffer;
    	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    	res = curl_easy_perform(curl);
    	
    	/* always cleanup */ 
    	curl_easy_cleanup(curl);
   		/* then cleanup the formpost chain */ 
    	curl_formfree(formpost);
		/* free slist */ 
    	curl_slist_free_all (headerlist);
   		if(CURLE_OK!=res){
   			sprintf(logs, "Could not send results. Curl Error code: %d\n", res);
   			Logs::WriteLine(logs);
   			
   		}	
   		else{
   			sprintf(logs, "Results sent succesfully.\n");
   			Logs::WriteLine(logs);
   		}
   		
  	}
}

bool CurlWrapper::ForcePushResult=true;
