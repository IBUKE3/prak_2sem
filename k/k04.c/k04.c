#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  int fd[2];
  if (pipe(fd)) return 1;
 
  int i = 0;
  while (strcmp(argv[i], "--")) i++;
  if (fork()==0) {
    close(fd[0]);
    dup2(fd[1], 1);
    argv[i] = NULL;
    close(fd[1]);
    execvp(argv[1], argv+1);
    exit(127);
  }


  pid_t pid;
  if ((pid=fork())==0) {
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    execvp(argv[i+1], argv + i + 1);
    exit(127);
  }

  close(fd[0]);
  close(fd[1]);

  int st;
  waitpid(pid, &st, 0);
  while (wait(NULL) != -1);

  return (WIFEXITED(st)?WEXITSTATUS(st):WTERMSIG(st)+128);
}
