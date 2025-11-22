#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

int main(void) {
  int fd[2];
  if (pipe(fd)) return 1;
  if (fork()==0) {
    close(fd[1]);
    int t;
    if(!read(fd[0], &t, sizeof(int))) exit(1);
    close(fd[0]);
    printf("%d\n", t);
    exit(0);
  }

  int pid;
  if ((pid=fork())==0) {
    close(fd[0]);
    close(fd[1]);
    usleep(10000);
    exit(0);
  }

  if (fork()==0) {
    close(fd[0]);
    if(!write(fd[1], &pid, sizeof(int))) exit(1);
    close(fd[1]);
    exit(0);
  }

  close(fd[0]);
  close(fd[1]);
  while(wait(NULL)!=-1);
  return 0;
}
