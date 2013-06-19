This guide will take you through the process of installing and running CodeRunner on your computer.


Dependencies	
==============	
CodeRunner uses Curl library for sending and receiving data over the network. The libcurl3, libcurl3-dev libraries should be installed before making build. On Ubuntu it can be installed by typing the command in the terminal- `sudo apt-get install libcurl3, libcurl3-dev`
Or otherwise, the packages can be downloaded from [here](curl.haxx.se) and installed on any linux flavour.


Installation Steps	
==============
1. Copy source code to the desired directory where you intend to run the CodeRunner.
2. Run the `./Install.sh` command on terminal. It should run without throwing any errors.
	*This script will add the required directories ans scripts to the CodeRunner with appropriate permissions.
	*This will also add config.h in `src` directory 
3. In the config.h file these options as required.
    * USERNAME and PASSWORD are the two fields which are sent to the website for authentication. Set them accordingly.
    * In case you want the CodeRunner to download source code files from website through FTP, then set FTPON option as `true` otherwise `false`. If you want the source code files to be downloaded through http request, then set HTTPON option to be `true` otherwise `false`. In case both options are true, then http option becomes the default choice.
    * FTPADDRESS is the ftp address from where CodeRunner will download the source files if FTPON option is true.
    * HTTPADDRESS is the http address from where CodeRunner will download the source files if HTTPON option is true.
    * FILEPATH is the address where the downloaded source files will be stored.
    * TESTCASESPATH is the address where test case input/output files of different problems are stored. By default it is set to `TestCases` folder in the PATH address by relative address mode.
    * URLToSendResults is the web address where CodeRunner will send the results of executed files.
    * LOGFILEPATH is the log file location where CodeRunner will log the results of files execution.
    * SLEEPINTERVAL is the time interval for which CodeRunner goes to sleep after one epoch.



