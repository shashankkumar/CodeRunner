/**
 * This is the sample config file for CodeRunner.
 * Before running make command, define the options suitably and
 * change the name of the file from sample.config.h to config.h
 * without which the source code will not compile.
 * All the options should be specified correctly for CodeRunner to work properly.
 * After that, simply run make command from command line.
 */

/**
 * The ABSOLUTE_PATH option should point to the folder in which CodeRunner is stored.
 */
#define ABSOLUTE_PATH "/home/shashank/git/CodeRunner/"

/** 
 * HTTPON and FTPON are two methods by which source code can be downloaded from internet.
 * If the preferred method is HTTP, then specify HTTPON as true.
 * otherwise specify FTPON as true.
 */
#define HTTPON true
#define FTPON false

/**
 * Specify the username and password to be used for communication over internet with the website.
 * The "username" and "password" fields will be supplied via POST request while querying for pending file ids, fetching source
 * code, and sending results.
 */
#define USERNAME "shashank"
#define PASSWORD "shashank"

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

/**
 * Specify the URL from where file ids and their evaluation relevant information like
 * problem id, time limit, etc will be fetched.
 * Same username and password will be used as above.
 */
#define URL_TO_GET_FILE_IDS "http://192.168.208.7/return_id.php"

/**
 * Specify the URL where results will be sent here.
 * Same username and password will be used as above.
 */
#define URL_TO_SEND_RESULTS "http://192.168.208.203/push_result.php"

/**
 * Specify the URL from where source code will be downloaded.
 * Same username and password will be used as above.
 */
#define URL_TO_GET_SOURCE_CODE "http://192.168.208.7/return_sourcecode.php"

/**
 * Path where downloaded source code files will be stored.
 */
#define FILEPATH "./Files/"

/**
 * Path where test cases are stored.
 */
#define TESTCASESPATH "./TestCases/"

/**
 * Path of log file directory.
 * Below that log file name.
 */
#define LOGFILEPATH "./Logs/"
#define LOGFILENAME "logs.txt"

/**
 * Specify the interval (in seconds) for which CodeRunner sleeps between two epochs.
 * One epoch is downloading of pending file ids, their source files, their execution and finally sending their results.
 */
#define SLEEPINTERVAL 5

/**
 * Specify the languages for which CodeRunner should evaluate solutions.
 * These options don't affect the working of CodeRunner as of now and will be supported in future versions.
 */
#define LANG_CPP true
#define LANG_JAVA true
#define LANG_PYTHON true
#define LANG_PERL true
