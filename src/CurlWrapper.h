#ifndef CURLWRAPPER_H
#define CURLWRAPPER_H
#include "headers.h"
#include "CROptions.h"

#include <curl/curl.h>
#include <curl/easy.h>

class CurlWrapper
{

	CURL *curl;
  CURLcode res;
  char logs[1000];
  	

           /*-------------------------------------Struct  Defination  Starts--------------------------------*/ 
    

  struct FtpFile 
  {
  	const char *filename;
  	FILE *stream;
	};
  

           /*-----------------------------------------Struct  Defination  Ends-----------------------------------*/



public:
  	CurlWrapper()
    {
  		curl_global_init(CURL_GLOBAL_DEFAULT);
      /*This function sets up the program environment that libcurl needs.
       *This function must be called at least once within a program before the program calls any other function in libcurl.
       *CURL_GLOBAL_DEFAULT : It will init both SSL and Win32 flags
       *If this function returns non-zero, something went wrong and you cannot use the other curl functions
       */
  		Logs::OpenLogFile();
  	}
  		
  	~CurlWrapper()
    {
  		curl_global_cleanup();
      /*This function releases resources acquired by curl_global_init().
       *Call curl_global_cleanup() once for each call made to curl_global_init()
       */
  	}
 
	static size_t ContentInFileFTP(void *buffer, size_t size, size_t nmemb, void *stream);
	static size_t ContentInVar(void* ptr, size_t size, size_t nmemb, string *stream);
	static size_t ContentInFileHTTP(void *ptr, size_t size, size_t nmemb, FILE *stream);
 	int GetFileFromFTP(int FileId);
	int GetFileFromHTTP(int FileId);
	int FetchContentFromWebPage(string *content);
	void SendResultsToWebpage(const char* fileid, const char* status, const char* detailstatus, const char* time, const char* memory, const char* numberofwrongtestcases);


};


#endif
