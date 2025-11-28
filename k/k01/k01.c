#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  int fd[2];
  if (pipe(fd)) return 1;
  
  if (fork()==0) {
    close(fd[0]);
    dup2(fd[1], 1);
    argv[argc-1] = NULL;
    close(fd[1]);
    execvp(argv[1], argv+1);
    exit(127);
  }

  if (fork()==0) {
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    execvp(argv[argc-1], argv + argc - 1);
    exit(127);
  }

  close(fd[0]);
  close(fd[1]);

  while(wait(NULL)!=-1);

  return 0;
}
