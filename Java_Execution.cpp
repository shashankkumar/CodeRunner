#include "includex.h"
#include "resources.h"

pid_t cpid;
void ToPipe(const char* str){
	printf("%s\n", str);
	return;
}
void signalHandler(int signum){
	if(cpid!=0){
		killpg(cpid,SIGKILL);
	}
}
int main(int args, char *argv[]){

	if(args<4){
		ToPipe("IE ERROR Not enough arguments.");
		return 1;
	}
	
	int TimeLimit, MemoryLimit, InputFileId, FileId;
	struct timeval start,finish;
    struct sigaction signalAction;
	pid_t w;
    int status;
    long long t_sec, t_usec;
    
    FileId = atoi(argv[1]), InputFileId = atoi(argv[2]), TimeLimit = atoi(argv[3]), MemoryLimit = atoi(argv[4]);
	
	signalAction.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT;
	signalAction.sa_handler = signalHandler;
	
	if(sigaction(SIGALRM, &signalAction, NULL)==-1){
		ToPipe("IE ERROR Could not register handler for sigalrm");
		return 1;
	}
	if(sigaction(SIGXCPU, &signalAction, NULL)==-1){
		ToPipe("IE ERROR Could not register handler fo rSIGXCPU");
		return 1;
	}
	gettimeofday(&start,NULL);
    cpid = fork();
    if (cpid == -1) { perror("fork"); exit(EXIT_FAILURE); }

    if (cpid == 0) {            /* Code executed by child */
		
		pid_t ChildProcessId = getpid();
		passwd* UserDetails = getpwnam("nobody");
		char dir[10];
		sprintf(dir, "%s%d/",FILEPATH,FileId);
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
		
		char InputFile[10], TestCaseFile[10], OutputFile[10];
		sprintf(InputFile, "main");
		sprintf(TestCaseFile, "%d.txt", InputFileId);
		sprintf(OutputFile, "%do.txt", InputFileId);
		if(freopen(TestCaseFile, "r", stdin)==NULL){
			ToPipe("IE ERROR Could not open test case file\n");
		}
		if(freopen(OutputFile, "w", stdout)==NULL){
			ToPipe("IE ERROR Could not open output file\n");
		}
		if(freopen("/dev/null", "w", stderr)==NULL){
			ToPipe("IE ERROR Could not redirect error stream to null\n");
		}
		Java_setResourceLimitWrapper(TimeLimit, MemoryLimit);
		alarm(TimeLimit);
		//if(execlp("/usr/bin/java", InputFile, NULL)== -1){
		if(execlp("/usr/bin/java","/usr/bin/java", "-Djava.security.manager","-classpath", "./","main",(char *) NULL)== -1){
			fclose(stdout);
			ToPipe("IE ERROR File not present or some other error.");
		}
		
	}
	else {                    /* Code executed by parent */

		struct rusage resourceUsage;
		w = wait4 (cpid, &status, NULL, &resourceUsage);
		
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
		
		if( WIFEXITED(status) == true ){
			if( WEXITSTATUS(status) !=0 ){
				ToPipe("RE NZEC");
			}
			else{
				ToPipe("AC");
			}
		}
		else if( WIFSIGNALED(status) == true ){
			if (WTERMSIG (status) == SIGKILL || WTERMSIG(status) == SIGALRM)
				ToPipe("TLE");
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
		printf("%d %d\n", (int)tv.tv_sec, (int)tv.tv_usec);
	}
}

