Documentation for Contest-Organizers
====================================
Problem Specifications

===

* The crux of a programming competition are its problems. While, the software has nothing to do with problem statements, the test cases need to be stored in proper format.
* The test cases are to be stored in the TESTCAESPATH directory path specified in config.h By default it is set to `TestCases` folder in the `PATH` address by relative address mode.
* Each problem should have a unique Problem Id. This string should be the means by which website and CodeRunner identifies a problem. For eg. PALIN, TEST etc.
* For every problem, there should be a folder present in TESTCASESPATH directory and its name should be the Problem Id. Before starting a competition, the problem directories should be created first. In each problem folder, there should be two folders named `Input` and `Output` without quotes. The Input folder should contain the input files for the problem, and the output folder should contain the output for the problem. Number the test case input and output files starting from 1. There is no limit on the number of test cases present for a problem. Corresponding input and output files should have the same number. So, suppose problem with problem id TEST has got 3 testcase files, then in the input folder, there should be 3 files namely 1, 2 and 3. And correspondingly in the output folder, there should be 3 files 1, 2 and 3. A solution submitted by the user is executed once for all the test cases. If the solution gives correct output for all the test cases, then only its status is changed to AC.
**Note:
In case there is a large body of problems and more will be uploaded over time (like in a practice arena, or a 24\*7 judge) then the process of uploading Test Cases (creating directories, and input and output files) can be automated through the website.

File List Specifiations
====
CodeRunner fetches the information of pending files from the URL `URLToFetchFileIds` specified in the config.h file. The format of specifying file ids in the webpage is as following:
    <FileId> <ProblemId> <TimeLimit> <MemoryLimit> <Language>
    
You can specify multiple file ids in the same format separated by \n as following:
  
    <FileId> <ProblemId> <TimeLimit> <MemoryLimit> <Language>
    <FileId> <ProblemId> <TimeLimit> <MemoryLimit> <Language>
    .
    .
    .
    <FileId> <ProblemId> <TimeLimit> <MemoryLimit> <Language>
    
There is no upper limit on the number of File Ids that can be specified in one display. 
The list of file ids supplied at a time to be executed is called an `Epoch` from now on.
However it is recommended not to supply more than 5-10 file ids at a time.
The <TimeLimit> is the number of seconds under which all the user solution should run for all the test cases.
The <MemoryLimit> is the maximum memory in MB that a solution can consume while running.
The <Language> is the language of the source code. Currently supported languages are C++, C, Java, Python, PHP, Perl. The corresponding string that should be supplied in <Language> options are `cpp, c, java, python, php, perl`. No other string should be specified in their place otherwise it may not function properly.

Results Specifications
==================
The results of execution of a file is sent to the URL `URLToSendResults` specified in the config.h file. The results are sent in the form of POST variables.
The variables are:
fileid, status, detailstatus, timeused, memoryused, numberofwrongtestcases
* The `fileid` variable will contain the File Id of the source code.
* The `status` variable will contain one of these codes: AC, CE, TLE, MLE, RE. 
* For few of these codes, `detailstatus` variable will further contain certain info as explained below:
* The `timeused` variable will contain the sum of execution time of the source file on all test cases of the problem.
* The `memoryused` variable contains the memory used by source file during execution.
* The `numberofwrongtestcases` variable returns how many lines of output file were mismatched with respect to the input file. In case  of multiple input/output files, numberofwrongtestcases returns the number of mismatches in the first input file where input does not match with output. This option is added on trial basis. If the test cases are such that every line in output file corresponds to one test case then numberofwrongtestcases returns the number of testcases which failed in a given input file.

Status code and their meaning
====
    AC ==> Accepted
    The `detailstatus` variable will not contain anything in this case.
    CE ==> Compilation Error
    The `detailstatus` variable will contain the compilation error string returned by compiler.
    RE ==> Runtime Error.
    The `detailstatus` variable will contain type of runtime error code. It will be one of following:
    SISSEGV, SIGFXZ, SIGNZEC, OTHER
    TLE ==> Time Limit Exceeded
    The `detailstatus` variable will not contain anything in this case.
    The `timeused` variable will simply be storing `0`.
    MLE ==> Memory Limit Exceeded
    If make did not give any compilation errors and you have set the options in config.h file correctly then, you are ready to run CodeRunner for the first time.

Commandline options
===
    -a ==> Fetch all file-ids irrespective of evaluation status.
    -b ==> For sending results and forcing insertion of those results.
    -c ==> Clear files directory after execution of source code.
    -d ==> Does not download source code. The source codes should already be present in the Files directory.
    -f ==> For pre-defining FileId. It is used when we are evaluating a particular file only. It has to be followed by additional(required) 
           parameter (ie the file id)
    -i ==> Excectute only one file
    -h ==> Print all command line options with their description
    -l ==> For pre-defining Language. It is used when we are evaluating a particular file only. It has to be followed by additional(required) 
           parameter (ie the language of the source program) 
    -m ==> For specifying pre-defined memory limit. It is used when we are evaluating a particular file only. It has to be followed by 
           additional(required) parameter (ie the max memory consumption (in MB) the program is allowed)
    -n ==> For not sending results after evaluation.
    -p ==> For pre-defining ProblemId. It is used when we are evaluating a particular file only. It has to be followed by additional(required) 
           parameter (ie the problem id)
    -q ==> quiet mode ie do not print output on screen
    -r ==> Run CodeRunner for just one epoch.
    -s ==> Specifying Sleep Interval after each epoch. It has to be followed by additional(required) parameter (ie sleep-inteval in seconds)
    -t ==> Specifying pre-defined time-limit. It is used when we are evaluating a particular file only. It has to be followed by additional(       required) parameter (ie the time limit in seconds)
    -v ==> For printing version related information.