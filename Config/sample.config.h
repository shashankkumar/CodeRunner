/**
 * This is the sample config file for CodeRunner.
 * Before running make command, define the options suitably and
 * change the name of the file from sample.config.h to config.h
 * without which the source code will not compile.
 * All the options should be specified correctly for CodeRunner to work properly.
 * After that, simply run make command from command line.
 */
#ifndef CONFIG_H
#define CONFIG_H
 /**
 * Specify the username and password to be used for communication over internet with the website.
 * The "username" and "password" fields will be supplied via POST request while querying for pending file ids, fetching source
 * code, and sending results.
 */
#define USERNAME "shashank"
#define PASSWORD "shashank"

/** 
 * HTTPON and FTPON are two methods by which source code can be downloaded from internet.
 * If the preferred method is HTTP, then specify HTTPON as true.
 * otherwise specify FTPON as true.
 */
#define HTTPON true
#define FTPON false

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


#define URL_TO_GET_FILE_IDS "http://localhost/projects/CodeRunner/Local/id.php"
#define URL_TO_GET_SOURCE_CODE "http://localhost/projects/CodeRunner/Local/sourcecode.php"
#define FILEPATH "./Files/"
#define TESTCASESPATH "./TestCases/"

/**
 * Specify the URL where results will be sent here.
 * Same username and password will be used as above.
 */
#define URL_TO_SEND_RESULTS "http://localhost:8089"

#define LOGFILEPATH "./Logs/"
#define LOGFILENAME "logs.txt"
/**
 * Specify the interval for which CodeRunner sleeps between two epochs.
 * One epoch is downloading of pending file ids, their source files, their execution and finally sending their results.
 */
#define SLEEPINTERVAL 30

#define LANG_CPP true
#define LANG_JAVA true
#define LANG_PYTHON true
#define LANG_PERL true
 