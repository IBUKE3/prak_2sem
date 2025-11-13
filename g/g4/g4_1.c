#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  if (fork()==0){
    execv(argv[1], argv+1);
    execvp(argv[1], argv+1); // trying execvp if execv falied
    exit(127);
  }
  int st = 0;
  wait(&st);
  if(WIFEXITED(st)) {
    printf("%d\n", WEXITSTATUS(st));
  } else {
    printf("%d\n", WTERMSIG(st));
  }

  return 0;
}
