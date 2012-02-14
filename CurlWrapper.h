#ifndef CURLWRAPPER_H
#define CURLWRAPPER_H
#include "headers.h"
#include "CROptions.h"

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

class CurlWrapper{

	CURL *curl;
  	CURLcode res;
  	char logs[1000];
  	struct FtpFile {
  		const char *filename;
  		FILE *stream;
	};

public:
  	CurlWrapper(){
  		curl_global_init(CURL_GLOBAL_DEFAULT);
  		Logs::OpenLogFile();
  		}
  		
  	~CurlWrapper(){
  		curl_global_cleanup();
  		}
 
	static size_t ContentInFileFTP(void *buffer, size_t size, size_t nmemb, void *stream);
	static size_t ContentInVar(void* ptr, size_t size, size_t nmemb, string *stream);
	static size_t ContentInFileHTTP(void *ptr, size_t size, size_t nmemb, FILE *stream);
 	int GetFileFromFTP(int FileId);
	int GetFileFromHTTP(int FileId);
	int FetchContentFromWebPage(string *content);
	void SendResultsToWebpage(const char* fileid, const char* status, const char* detailstatus, const char* time, const char* memory);
};

#endif
