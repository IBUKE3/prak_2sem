#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  if (fork()==0){
    execvp(argv[1], argv+1);
    exit(127); // an error occured during execlp
	       // ОБЯЗАТЕЛЬНЫЙ EXIT
  }
  int st = 0;
  wait(&st);
  if(WIFEXITED(st)) {
    printf("exited with status: %d\n", WEXITSTATUS(st));
  }
}
