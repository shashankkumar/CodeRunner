Documentation for Developers
====================================

Commands used for excecuting the programs in different languages
===

For C++ :
    
    Compilation: 
        `g++ -w -static FullFileAddr.cpp -o FullFileAddr 2>&1`


For C :

    Compilation:
        `gcc -w -static FullFileAddr.c -o FullFileAddr 2>&1`
    

For Java :

    Compilation:
        `javac FullFileAddr.java`


For Python : 
    
    Syntax Check:
        `python -m py_compile FullFileAddr.py`


For Pascal : 

    Syntax Check : 
        `fpc FullFileAddr.p`


For Perl : 

    Syntax Check : 
        `perl -c FullFileAddr.pl`


For PHP :

    Syntax Check : 
        `php -l FullFileAddr.php`


    
Measuirng memory usage by a program
===

CodeRunner uses [proc](http://serverfault.com/questions/301980/in-unix-linux-what-is-the-proc-directory-for-why-does-it-exists) to determine memory usage by programs. For almost every process running in the system, there is a directory created in /proc/. The directory name is the process id and it contains several useful files including a file called `status`.

**/proc/[pid]/status** : This file contains information regarding memory usage such as virtual memory size (VmSize), size of data segment (VmData), stack size (VmStk), and size of text segment (VmExe). All these sizes are in KB ie KiloBytes.

Sample Output for `cat /proc/3159/status` :


    Name:   chrome
    State:  S (sleeping)
    Tgid:   3159    
    Pid:    3159
    PPid:   2490
    TracerPid:  0
    Uid:    1000    1000    1000    1000
    Gid:    1000    1000    1000    1000
    FDSize: 256
    Groups: 4 24 27 30 46 109 124 1000 
    VmPeak:   362948 kB
    VmSize:   362948 kB
    VmLck:         0 kB
    VmPin:         0 kB
    VmHWM:    136272 kB
    VmRSS:    136036 kB
    VmData:   190464 kB
    VmStk:       136 kB
    VmExe:     83228 kB
    VmLib:     49076 kB
    VmPTE:       612 kB
    VmSwap:        0 kB
    Threads:    28
    SigQ:   0/23036
    SigPnd: 0000000000000000
    ShdPnd: 0000000000000000
    SigBlk: 0000000000000000
    SigIgn: 0000000004001002
    SigCgt: 00000001c0010000
    CapInh: 0000000000000000
    CapPrm: 0000000000000000
    CapEff: 0000000000000000
    CapBnd: ffffffffffffffff
    Cpus_allowed:   f
    Cpus_allowed_list:  0-3
    Mems_allowed:   1
    Mems_allowed_list:  0
    voluntary_ctxt_switches:    30213
    nonvoluntary_ctxt_switches: 17173


The fields of interest are as follows:

* Name: Command run by this process.

* State: Current state of the process.  One of "R (running)", "S
  (sleeping)", "D (disk  sleep)",  "T  (stopped)",  "T  (tracing
  stop)", "Z (zombie)", or "X (dead)".

* VmPeak: Peak virtual memory size.

* VmSize: Virtual memory size.

* VmLck: Locked memory size (see mlock(3)).

* VmHWM: Peak resident set size ("high water mark").

* VmRSS: Resident set size.

* VmData, VmStk, VmExe: Size of data, stack, and text segments.

* VmLib: Shared library code size.

* VmPTE: Page table entries size (since Linux 2.6.10).

* Threads: Number of threads in process containing this thread.

For detailed information about these terms, refer to man page of `proc`

Note : I read some where that **data segment = data+bss+heap**

**/proc/[pid]/statm**: This files also contains information about memory usage. The file has a single row of information where values are placed separated by space. These values are total program size, resident set size, size of shared pages, size of text segment, size of lib code, size of data segment + stack, and  dirty pages.

Sample Output for `cat /proc/3159/statm` :


    90737 34018 5151 20807 0 47650 0


We prefer /proc/[pid]/status over /proc/[pid]/statm because former uses KB for expressing memory size while latter uses number of pages. Assuming that 1 page = 4 KB (this is the usual case but not the general case), we can get memory usage in KBs.

We are interested in computing memory usgae of the program which is given as : **memory usage =  size of data + size of bss + size of heap + size of stack**.

**VmData = size of data + size of bss + size of heap** 

**VmStk = size of stack**.

This means **memory usage = VmData + VmStk**


Implementation :

`MemoryUsage` function in Execution.cpp returns the total memory used by the program in terms of KBs. The `p` variable defined in the function contains the output of /proc/[pid]/status.

Shortcomings : 

*   VmData and heap size can be inaccurate as kernel may allocate more memory than asked for making execution effecient.

Currently MemoryUsed = max(64, MemoryUsage(cpid)) ie the MemoryUsed is reported as maximum of 64 or actual Memory Usage by the program.



Measuirng time take by a program
===
There are two cases : 

*   Time Limit Not Exceeded : In this case, the total time taken by the program is stored in `TimeUsed` variable in `Execution.cpp`.
*   Time Limit Exceeded : In this case, the program gets killed after `t` seconds as specified in time limit of the program and `TLE` status is returned.

Relevant resource limits are defined in `resources.h`



Securing C/C++ Submissions
===
 
 `gcc -w -I ../../gcc -static` The additional -I flag make the compiler look into 'gcc' folder instead of the default locations. The 'gcc' folder contains a copy of files like 'unistd.h', 'syslimits.h', 'bits/', 'linux/', 'sys' etc. This way if the submission makes a request to these files or files in these folders, then it returns compilation error (CE). So we need to make a copy of all such files in a seperate folder called 'gcc' on the server running CodeRunner. Also 'gcc' folder should be in the same directory as CodeRunner.



Securing Java Submissions
===
To secure java submissions, we rely on enabling Java Security Manager and specifying policy files. 

`java -Djava.security.manager -Djava.security.policy==./policy.txt` This command replaces the default privileges with the privileges given in [policy.txt](https://github.com/shashankkumar/CodeRunner/blob/master/policy.txt). Current configuration blocks access to all networking and OS operations and does not need any change.

Further details about it can be found [here](http://pic.dhe.ibm.com/infocenter/cicsts/v4r1/index.jsp?topic=%2Fcom.ibm.cics.ts.java.doc%2Ftopics%2Fdfhpj5u.html).

Refer [this](http://stackoverflow.com/questions/11620354/running-java-security-manager-without-the-default-java-policy-file) for differentiating between use of '=' and '==' while running Java Security Manager. 