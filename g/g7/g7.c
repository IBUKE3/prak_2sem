#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
  if (fork()==0) {
    execlp(argv[1], *(argv+1), NULL);
    exit(127);
  }

  int status;
  wait(&status);

  if (fork()==0) {
    execvp(argv[2], argv+2);
    exit(127);
  }

  wait(&status);

  if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  } else {
    return 128+WTERMSIG(status);
  }

}
