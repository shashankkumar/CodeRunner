#ifndef CONFIG
#define CONFIG
#define USERNAME ""
#define PASSWORD ""
#define FTPUSERNAME ""
#define FTPPASSWORD ""
#define FTPADDRESS "/Upload/"
#define URLToGetFileIds "http://192.168.208.208/codevillage/return_id_new.php"
#define FTPON false
#define HTTPON true
#define HTTPADDRESS "http://192.168.208.208/codevillage/fileNew.php"
#define FILEPATH "./Files/"
#define TESTCASESPATH "./TestCases/"
#define URLToSendResults "http://192.168.208.208/codevillage/update_result2.php"
#define FetchFileFromFTP true

void ToLogs(const char* log){
	printf("%s\n",log);
	return;
}
#endif
