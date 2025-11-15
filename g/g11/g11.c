#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main(int argc, char* argv[]) {
  if (fork()==0) {
    
    int fd = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0666);
    dup2(fd, 1);

    if (fork()==0) {
      execlp(argv[1], argv[1], NULL);
      exit(127);
    }

    int status;
    wait(&status);

    if (WIFEXITED(status) && !status) exit(status); // first success
    if (fork()==0) {
      execlp(argv[2], argv[2], NULL);
      exit(127);
    }
    wait(&status);
    exit(status);
  }

  int st;
  wait(&st);

  if (WIFEXITED(st)&&WEXITSTATUS(st)==0) {
    if (fork()==0) {
      execlp(argv[4], argv[4], NULL);
      exit(127);
    }
  } else {
    return WIFEXITED(st) ? WEXITSTATUS(st) : 128 + WTERMSIG(st);
  }

  wait(&st);
  return WIFEXITED(st) ? WEXITSTATUS(st) : 128 + WTERMSIG(st);

}
