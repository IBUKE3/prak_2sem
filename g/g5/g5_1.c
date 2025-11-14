#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[]){
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
    execv(argv[1], argv+1);
    execvp(argv[1], argv+1);
    exit(127);
  }

  int st = 0;
  wait(&st);
  if(WIFEXITED(st)&&WEXITSTATUS(st)==0) {
    argv[sz-1] = tq;
    if (fork()==0) {
      execv(argv[sz-1], argv+sz-1);
      execvp(argv[sz-1], argv+sz-1);
      exit(127);
    }
  }


  return 0;
}

