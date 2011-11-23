#include "includes.h"
#include "resources.h"
#include "config.h"

pid_t cpid;
const int MicroSecSleepInterval = 71;
void ToPipe(const char* str){
	printf("%s\n", str);
	return;
}

void SignalHandler(int signum){
	if(cpid!=0){
		killpg(cpid,SIGKILL);
	}
}

/* high resolution (microsecond) sleep */
void MicroSecSleep (int ms){
	struct timeval tv;
	int w;
	do{
		tv.tv_sec = ms / 1000;
		tv.tv_usec = (ms % 1000) * 1000;
		w = select (0, NULL, NULL, NULL, &tv);
		/* The value of the timeout is undefined after the select returns */
	} while ((w < 0) && (errno == EINTR));
	if (w < 0)
		ToPipe("IE ERROR Failed while calling select in microsleep");
}

int MemoryUsage(pid_t cpid){
	char a[10000], *p, *q;
	int data, stack;
	int rss; /* ZP */
	int n, v, fd;

	p = a;
	sprintf (p, "/proc/%d/status", cpid);
	fd = open (p, O_RDONLY);
	if (fd < 0)
		ToPipe("IE ERROR Failed to open /proc/pid/status") ;
	do{
		n = read (fd, p, 10000);
	} while ((n < 0) && (errno == EINTR));
	if (n < 0)
		ToPipe("IE ERROR Failed to read /proc/pid/status") ;
	do{
	v = close (fd);
	} while ((v < 0) && (errno == EINTR));
	if (v < 0)
		ToPipe("IE ERROR Failed to close file descriptor for /proc/pid/status") ;

	rss = data = stack = 0; 
	q = strstr (p, "VmData:");
	if (q != NULL)
	{
		sscanf (q, "%*s %d", &data);
		q = strstr (q, "VmStk:");
		if (q != NULL)
			sscanf (q, "%*s %d\n", &stack);

		q = strstr (q, "VmRSS:");
		if (q != NULL)
			sscanf (q, "%*s %d\n", &rss);
		else
			rss = data + stack;
	}

	return min(data + stack, rss);
	/* return (data + stack); */
}

int main(int args, char *argv[]){

	if(args<4){
		ToPipe("IE ERROR Not enough arguments.");
		return 1;
	}
	
	int TimeLimit, MemoryLimit, TestCaseFileId, FileId;
	char InputFile[10];
	struct timeval start,finish;
    struct sigaction SignalAction;
	pid_t w;
    int status;
    long long t_sec, t_usec;
    
    FileId = atoi(argv[1]), strcpy(InputFile, argv[2]);
    TestCaseFileId = atoi(argv[3]), TimeLimit = atoi(argv[4]), MemoryLimit = atoi(argv[5]);
	
	SignalAction.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT;
	SignalAction.sa_handler = SignalHandler;
	
	if(sigaction(SIGALRM, &SignalAction, NULL)==-1){
		ToPipe("IE ERROR Could not register handler for SIGALRM");
		return 1;
	}
	if(sigaction(SIGXCPU, &SignalAction, NULL)==-1){
		ToPipe("IE ERROR Could not register handler fo SIGXCPU");
		return 1;
	}
	
	gettimeofday(&start,NULL);
	cpid = fork();
    if (cpid == -1) { perror("fork"); exit(EXIT_FAILURE); }

    if (cpid == 0) {            /* Code executed by child */
		
		pid_t ChildProcessId = getpid();
		passwd* UserDetails = getpwnam("nobody");
		char dir[10];
		sprintf(dir, "%s%d/", FILEPATH, FileId);
		//ToPipe(dir);
		if( chdir(dir) == -1){
			printf("%d", errno);
			ToPipe("IE ERROR Cannot change directory to that of file");
			return 1;
		}
		
		//ToPipe(get_current_dir_name());
		/*if(chroot(get_current_dir_name())!=0){
			ToPipe("IE ERROR Cannot jail the program");
			return 1;
		}*/
		
		if(( setpgid( ChildProcessId, ChildProcessId) ) == -1 ){
			ToPipe("IE ERROR process group could not be created\n");
			return 1;
		}
		
		if(UserDetails!=NULL){ 
			gid_t GroupId = UserDetails->pw_gid;
			if( GroupId > 0 ){
				setgid( GroupId );
			}
			else{
				ToPipe("IE ERROR Could not set groupid as groupid is invalid\n");
				return 1;
			}
			uid_t UserId = UserDetails->pw_uid;
			if( UserId > 0 ){
		 		setuid(UserId);
		 	}
			else{
				ToPipe("IE ERROR Failed to set userid as it is invalid\n");
				return 1;
			}
		} 
		else{ 
			ToPipe("IE ERROR No user id associated with user nobody\n");
			return 1; 
		}
		
		char TestCaseFile[10], OutputFile[10];
		sprintf(TestCaseFile, "%d.txt", TestCaseFileId);
		sprintf(OutputFile, "%do.txt", TestCaseFileId);
		if(freopen(TestCaseFile, "r", stdin)==NULL){
			ToPipe("IE ERROR Could not open test case file\n");
		}
		if(freopen(OutputFile, "w", stdout)==NULL){
			ToPipe("IE ERROR Could not open output file\n");
		}
		if(freopen("/dev/null", "w", stderr)==NULL){
			ToPipe("IE ERROR Could not redirect error stream to null\n");
		}
		SetResourceLimitValues(TimeLimit);
		alarm(TimeLimit);
		if(execl(InputFile,InputFile,(char *) NULL) == -1){
			fclose(stdout);
			ToPipe("IE ERROR File not present or some other error.");
		}
		
	}
	else {                    /* Code executed by parent */
		struct rusage resourceUsage;
		
		int MemoryUsed = 0;
		
		do{
			MicroSecSleep(MicroSecSleepInterval);
			MemoryUsed = max(MemoryUsed, MemoryUsage(cpid));
			if(MemoryUsed > MemoryLimit){
				kill(cpid, SIGKILL);
			}
			w = wait4 (cpid, &status, WUNTRACED | WCONTINUED, &resourceUsage);
		} while(w==0);
		
		gettimeofday(&finish,NULL);
		t_sec = finish.tv_sec-start.tv_sec;
		t_sec=finish.tv_sec-start.tv_sec;
		t_usec=finish.tv_usec-start.tv_usec;
		if(t_usec<0){
			t_sec--;
			t_usec+=1000000;
		}	
		
		timeval tv = resourceUsage.ru_utime;
		float SysTime = (float)(  tv.tv_sec * 1000000 + (int) tv.tv_usec ) / 1000000 ;
		float TimeUsed = (float)( t_sec * 1000000 + (int) t_usec ) / 1000000 ;
		
		bool sigkill = false, sigalrm = false;
		
		if(MemoryUsed > MemoryLimit){
			;
		}
		else if( WIFEXITED(status) == true ){
			if( WEXITSTATUS(status) !=0 ){
				ToPipe("RE NZEC");
			}
			else{
				ToPipe("AC");
			}
		}
		else if( WIFSIGNALED(status) == true ){
			if (WTERMSIG (status) == SIGKILL ){
				ToPipe("TLE");
				sigkill = true;
			}
			else if (WTERMSIG(status) == SIGALRM){
				ToPipe("TLE");
				sigalrm = true;
			}
		    else if (WTERMSIG (status) == SIGXFSZ)
				ToPipe("RE SIGXFSZ");
			else if (WTERMSIG (status) == SIGSEGV)
				ToPipe("RE SIGSEGV");
			else if (WTERMSIG (status) == SIGFPE)
				ToPipe("RE SIGFPE");
			else if (WTERMSIG (status) == SIGABRT)
				ToPipe("RE SIGABRT");
		    else if (WTERMSIG (status) == SIGHUP)
				ToPipe("IE SIGHUP");
		    else if (WTERMSIG (status) == SIGPIPE)
				ToPipe("IE SIGPIPE");
		    else{
				ToPipe("RE OTHER");
				printf("%d\n", WTERMSIG(status));
			}
		}
		char tmp[10];
		sprintf(tmp, "%0.4f", TimeUsed);
		ToPipe(tmp);
		sprintf(tmp, "%d", MemoryUsed);
		ToPipe(tmp);
		//printf("%d %d\n", (int)tv.tv_sec, (int)tv.tv_usec);
		if(sigkill) printf("SIGKILL");
		else if(sigalrm) printf("SIGALRM");
	}
}
