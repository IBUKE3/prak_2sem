#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main(int argc, char* argv[]) {
  int fd[2];

  if (pipe(fd)==-1) return 1;

  if (fork()==0) { 
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);

    if (fork()==0) {
      execlp(argv[1], argv[1], NULL);
      exit(127);
    }

    int status;
    wait(&status);

    if (WIFEXITED(status) && !WEXITSTATUS(status)) exit(0); // first success
						    
    if (fork()==0) {
      execlp(argv[2], argv[2], NULL);
      exit(127);
    }

    wait(&status);

    exit(WIFEXITED(status) ? WEXITSTATUS(status) : 128 + WTERMSIG(status));
  }

  pid_t pid;
  if ((pid=fork())==0) {
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    execvp(argv[3], argv+3);
  }
  
  close(fd[0]);
  close(fd[1]);

  int st;
  waitpid(pid, &st, 0);
  while(wait(NULL)!=-1);
  return WIFEXITED(st) ? WEXITSTATUS(st) : 128 + WTERMSIG(st);

}
