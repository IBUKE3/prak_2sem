#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void) {
  int fd[2];
  int flag = 0;
  char byte;
  if (pipe(fd)==-1) return 1;

  if (fork()==0) {
    close(fd[0]);
    while (read(0, &byte, 1)) {
      if (flag) write(fd[1], &byte, 1); 
      flag = ~flag;
    }
    close(fd[1]);
  }

  if (fork()==0) {
    close(fd[1]);
    if (fork()==0) {
      while (read(fd[0], &byte, 1)) {
        if (flag) write(1, &byte, 1);
	flag = ~flag;
      }
      close(fd[0]);
    }
  }

  close(fd[0]);
  close(fd[1]);
  int status;
  while (wait(&status) != -1);
  return 0;
}

