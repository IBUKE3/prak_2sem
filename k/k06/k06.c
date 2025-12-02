#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void){
  int fd1[2], fd2[2];
  if (pipe(fd1)==-1) return 1;

  // grep '(' | cut -d '(' -f 1 | sort -u

  if (fork()==0) {
    close(fd1[0]);
    dup2(fd1[1], 1);
    close(fd1[0]);
    execlp("grep", "grep", "[^ ](", NULL); 
    exit(127);
  }

  if (pipe(fd2)==-1) return 1; 
  if (fork()==0) {
    close(fd1[1]);
    close(fd2[0]);
    dup2(fd1[0], 0);
    close(fd1[1]);
    dup2(fd2[1], 1);
    close(fd2[1]);

    execlp("cut", "cut", "-d", "(", "-f", "1", NULL);
    exit(127);
  }

  pid_t p;
  if ((p=fork()) == 0) {
    close(fd1[1]);
    close(fd1[0]);
    close(fd2[1]);
    dup2(fd2[0], 0);
    close(fd2[0]);

    execlp("sort", "sort", "-u", NULL);
    exit(127);
  }

  close(fd1[0]);
  close(fd1[1]);
  close(fd2[0]);
  close(fd2[1]);

  while(wait(NULL)!=-1);
  

  return 0;
}

