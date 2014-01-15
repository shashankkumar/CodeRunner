#include "CROptions.h"


bool CROptions::RunOnce = false;
unsigned int CROptions::SleepInterval = SLEEPINTERVAL;
const char* CROptions::PATH = ABSOLUTE_PATH;
const char* CROptions::TestCasesPath = TESTCASESPATH;
const char* CROptions::URLToGetFileIds = URL_TO_GET_FILE_IDS;
const char* CROptions::FilesPath = FILEPATH;
const char* CROptions::URLToSendResults = URL_TO_SEND_RESULTS;
const char* CROptions::LogFilePath = LOGFILEPATH;
const char* CROptions::LogFileName = LOGFILENAME;
const char* CROptions::URLToGetSourceCode = URL_TO_GET_SOURCE_CODE;
const char* CROptions::username = USERNAME;
const char* CROptions::password = PASSWORD;
bool CROptions::lang_c = LANG_C;
bool CROptions::lang_cpp = LANG_CPP;
bool CROptions::lang_java = LANG_JAVA;
bool CROptions::lang_php = LANG_PHP;
bool CROptions::lang_python = LANG_PYTHON;
bool CROptions::lang_perl = LANG_PERL;
bool CROptions::ForcePushResult = FORCE_PUSH_RESULT;
bool CROptions::GetAllFileIds = GET_ALL_FILEIDS;
bool CROptions::Clean = CLEAN;
bool CROptions::SendResults = SEND_RESULTS;
bool CROptions::DownloadSourceFile = DOWNLOAD_SOURCE_FILE;
bool CROptions::OneFileExecution = ONE_FILE_EXECUTION;
bool CROptions::PrintOnScreen = PRINT_ON_SCREEN;
bool CROptions::Verbose = VERBOSE;
CROptions::FileInfoFetchOptionsStruct *CROptions::FileInfoFetchOptions = new CROptions::FileInfoFetchOptionsStruct();
