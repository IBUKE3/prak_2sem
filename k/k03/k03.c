#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  int fd[2];
  int file = open(argv[1], O_RDWR, 0644);

  if (pipe(fd)) return 1;
  
  int x;
  
  if (fork()==0) {
    close(fd[0]);
    if (!read(file, &x, sizeof(int))) exit(1);
    x++;
    if (!write(fd[1], &x, sizeof(int))) exit(1);
    close(fd[1]); 
    close(file); 
    exit(0);
  }

  if (fork()==0) {
    close(fd[1]);
    if (!read(fd[0], &x, sizeof(int))) exit(1);
    x++;
    lseek(file, 0, SEEK_SET);
    if (!write(file, &x, sizeof(int))) exit(1);
    close(fd[0]);
    close(file);
    exit(0);
  }

  close(fd[0]);
  close(fd[1]);
  while(wait(NULL)!=-1);
  return 0;
}
