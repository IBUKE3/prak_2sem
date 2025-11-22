#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


int main(void) {
 
  const char* file = "tmp.txt";

  int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // права обязательно
  close(fd);
  if (fork() == 0) {
    execlp("ls", "ls", "-l", file, NULL);
    exit(127);
  }

  wait(NULL);




  fd = open(file, O_RDWR);
  if(!write(fd, "Hello!\n", 7)) return 1;

  unlink(file);
  printf("suces\n");




  if (fork() == 0) {
    execlp("ls", "ls", "-l", file, NULL);
    exit(127);
  }
  wait(NULL);

  char buf[10] = {};
  lseek (fd, 0, SEEK_SET);
  if(!read(fd, buf, 9)) return 1;
  printf("Zombie content: %s", buf);

  close(fd);

}


