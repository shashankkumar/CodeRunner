#ifndef CURLWRAPPER
#define CURLWRAPPER
#include "includes.h"
class CurlWrapper{
public:
	CURL *curl;
  	CURLcode res;
  	char logs[1000];
  	
  	CurlWrapper(){
  		curl_global_init(CURL_GLOBAL_DEFAULT);
  		}
  		
  	~CurlWrapper(){
  		curl_global_cleanup();
  		}
 
	struct FtpFile {
  		const char *filename;
  		FILE *stream;
	};

	static size_t ContentInFileFTP(void *buffer, size_t size, size_t nmemb, void *stream);
	static size_t ContentInVar(void* ptr, size_t size, size_t nmemb, string *stream);
	static size_t ContentInFileHTTP(void *ptr, size_t size, size_t nmemb, FILE *stream);

 	int GetFileFromFTP(int FileId);
	int GetFileFromHTTP(int FileId);
	int FetchContentFromWebpage(string *content);
	void SendResultsToWebpage(const char* fileid, const char* status, char* detailstatus, const char* time, const char* memory);
	
};

#endif
