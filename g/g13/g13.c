#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  if (fork() == 0) {
    int fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0666);
    dup2(fd, 1);
    close(fd);
    execlp(argv[1], argv[1], NULL);
    exit(127);
  }

  int st;
  wait(&st);

  if (!(WIFEXITED(st) && WEXITSTATUS(st)==0)) {
    if (fork()==0) {
      execlp(argv[3], argv[3], NULL);
      exit(127);
    }
    wait(&st);
  }
  return(WIFEXITED(st) ? WEXITSTATUS(st) : 128 + WTERMSIG(st));
}
