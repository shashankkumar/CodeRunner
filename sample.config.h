/**
 * This is the sample config file for CodeRunner.
 * Before running make command, define the options suitably and
 * change the name of the file from sample.config.h to config.h
 * without which the source code will not compile.
 * All the options should be specified correctly for CodeRunner to work properly.
 * After that, simply run make command from command line.
 */

#define USERNAME "shashank"
#define PASSWORD "shashank"
#define FTPON false
#define HTTPON true
#define FTPUSERNAME ""
#define FTPPASSWORD ""
#define FTPADDRESS "/Upload/"
#define URLToGetFileIds "http://192.168.208.7/return_id.php"
#define HTTPADDRESS "http://192.168.208.7/return_sourcecode.php"
#define FILEPATH "./Files/"
#define TESTCASESPATH "./TestCases/"
#define URLToSendResults "http://192.168.208.203/push_result.php"
#define FetchFileFromFTP true
#define LOGFILEPATH "./Logs/logs2.txt"
#define SLEEPINTERVAL 30

/**
 * The PATH option should point to the folder in which CodeRunner is stored.
 */
#define PATH "/home/shashank/git/CodeRunner/"
