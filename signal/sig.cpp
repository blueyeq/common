#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <error.h>
#include <sys/time.h>

void sig_chld(int signo){

	printf("child process\n");
}

void sig_alarm(int signo){
	printf("alarm %d\n", getpid());
}
void test_alarm(){
	
	itimerval value, ovalue;
	value.it_value.tv_sec = 0;
	value.it_value.tv_usec = 100000;
	value.it_interval.tv_sec = 0;
	value.it_interval.tv_usec = 100000;

	pid_t pid = fork();
	printf("process id =%d\n", getpid());
	setitimer(ITIMER_REAL, &value, &ovalue);
}
int main(){

	pid_t pid;
    int status;
    signal(SIGCHLD,sig_chld);
	signal(SIGALRM, sig_alarm);
	pid = getpid();	
	pid = fork();
	itimerval value, ovalue;
	value.it_value.tv_sec = 1;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 1;
	value.it_interval.tv_usec = 0;

	//printf("process id =%d\n", getpid());
	setitimer(ITIMER_REAL, &value, &ovalue);
	//test_alarm();
	while(1);
	if(pid == 0){
		//printf("Child pid: %d\n",getpid());
	}
	else if(pid > 0){
		//waitpid(pid,&status,0);
		//printf("Parent pid: %d, status: %d\n",getpid(),status);
	}
	exit(0);
}
