#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
  int fd = open(argv[2], O_RDONLY);
  dup2(fd, 0);
  if (fork()==0) {
    execlp(argv[1], argv[1], NULL);
    exit(127);
  }

  int status;
  wait(&status);
/*
 if(WIFEXITED(status)) {
	    printf("%d\n", WEXITSTATUS(status));
	     } else {
		        printf("%d\n", WTERMSIG(status));
		         }	
*/
  return 0;
}
