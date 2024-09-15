#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
	int pipe1[2], pipe2[2];
	char msg[16];
	
	pipe(pipe1);
	pipe(pipe2);
	
	if(fork() == 0){
		//child process
		
		//close write end of its read pipe.
		close(pipe1[1]);
		
		//writing for parent to read
		write(pipe2[1], "From Child", 10);	
		
		read(pipe1[0], msg, 11);	
		printf("(%s): received by child.\n", msg);
		
		exit(0);	
	}
	else{
		//parent process
		
		//close write end of its read pipe.
		close(pipe2[1]);
		
		//writing for parent to read
		write(pipe1[1], "From Parent", 11);	
		
		read(pipe2[0], msg, 10);
		wait(0);	
		printf("(%s): received by parent.\n", msg);
	}	
	
	exit(0);
}
