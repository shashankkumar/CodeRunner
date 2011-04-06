#ifndef CONFIG
#define CONFIG
#define USERNAME "shashank"
#define PASSWORD "shashank"
#define FTPUSERNAME "sdscodevillage"
#define FTPPASSWORD "work1nghardandfast"
#define FTPADDRESS "ftp://192.168.208.208/Upload/"
#define URLToGetFileIds "http://192.168.208.208/codevillage/return_id_new.php"
#define FTPON false
#define HTTPON true
#define HTTPADDRESS "http://192.168.208.208/codevillage/fileNew.php"
#define FILEPATH "./Files/"
#define TESTCASESPATH "./TestCases/"
#define URLToSendResults "http://192.168.208.208/codevillage/update_result2.php"
#define FetchFileFromFTP true

FILE * logFile;

void ToLogs(const char* log){
	printf("%s\n",log);
	logFile = fopen("logs.txt", "a");
	fputs(log, logFile);
	return;
}
#endif
