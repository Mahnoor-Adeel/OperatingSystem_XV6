#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {

	if(argc<2){
		printf("System calls for this program: %d\n", callcount(getpid()));
		exit(0);
	}
	
	int pid = fork();
	
	if(pid<0){
		printf("Forking error\n");	
		exit(0);
	}
	
	if(pid == 0){	
		//child process
		exec(argv[1], &argv[1]);
				
		exit(0);
	}
	else{
		//parent process
		printf("pid: %d\n", pid);
		
		//get callcount for child process.
		//subtracting 1 to ignore exec.	
		int call_count = callcount(pid)-1;
		wait(0);
		printf("%d system calls in %s.\n", call_count, argv[1]);
		
		exit(0);
	
	}	
	exit(0);

}
