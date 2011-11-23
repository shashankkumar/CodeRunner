/**
 * This is the sample config file for CodeRunner.
 * Before running make command, define the options suitably and
 * change the name of the file from sample.config.h to config.h
 * without which the source code will not compile.
 * All the options should be specified correctly for CodeRunner to work properly.
 * After that, simply run make command from command line.
 */

/**
 * The PATH option should point to the folder in which CodeRunner is stored.
 */
#define PATH "/home/shashank/git/CodeRunner/"

/**
 * Specify the username and password to be used for communication over internet with the website.
 * The "username" and "password" fields will be supplied via POST request while querying for pending file ids, fetching source
 * code, and sending results.
 */
#define USERNAME "shashank"
#define PASSWORD "shashank"

/** HTTPON and FTPON are two methods by which source code can be downloaded from internet.
 * If the preferred method is HTTP, then specify HTTPON as true.
 * otherwise specify FTPON as true.
 */
#define FTPON false
#define HTTPON true

/**
 * If the preferred method for source code download is FTP, then specify the FTP username
 * and password field to be user during authentication in here.
 */
#define FTPUSERNAME ""
#define FTPPASSWORD ""

/**
 * Specify the FTP url for downloading source code files here.
 */
#define FTPADDRESS "/Upload/"


#define URLToGetFileIds "http://192.168.208.7/return_id.php"
#define HTTPADDRESS "http://192.168.208.7/return_sourcecode.php"
#define FILEPATH "./Files/"
#define TESTCASESPATH "./TestCases/"
#define URLToSendResults "http://192.168.208.203/push_result.php"
#define FetchFileFromFTP true
#define LOGFILEPATH "./Logs/logs2.txt"
#define SLEEPINTERVAL 30

