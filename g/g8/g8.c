#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
  char** cq = argv;
  int sz = 0;
  while(*cq) {
    sz++;
    cq++;
  }
  if (sz < 3) return 1;
  char* tq = argv[sz-1];
	     
  argv[sz-1] = NULL;
  if (fork()==0) {
    execvp(argv[1], argv+1);
    exit(127);
  }

  int status;
  wait(&status);

  if (WIFEXITED(status) && !status) return 0; // first ran successfully

  if (fork()==0) {
    execlp(tq, tq, NULL);
    exit(127);
  }

  wait(&status);

  return 0;

}
