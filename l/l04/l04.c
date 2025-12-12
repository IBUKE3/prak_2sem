#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static volatile int p1_flag = 0;
static volatile int p2_flag = 0;

void sghdlr(int s) {
  if (s == SIGUSR1) {
    p2_flag = 1;
  }
  if (s == SIGUSR2) {
    p1_flag = 1;
  }
}


void update_file(int fd) {
  int n;
  lseek(fd, SEEK_SET, 0);
  read(fd, &n, sizeof(n));
  lseek(fd, SEEK_SET, 0);
  n++;
  write(fd, &n, sizeof(n));
}


int main(void) {
  int N;
  setbuf(stdout, 0);

  signal(SIGUSR1, sghdlr);
  signal(SIGUSR2, sghdlr); 

  pid_t sons[50];

  if(!scanf("%d", &N)) return 1;

  char tmp[] = "tmpXXXXXX";
  int fd = mkstemp(tmp);
  unlink(tmp); 

  int r = 0;
  lseek(fd, SEEK_SET, 0);
  write(fd, &r, sizeof(r));

  p1_flag = 1;

  for (int j = 0; j < N; j++) {
    if ((sons[j]=fork())==0) {
      pid_t father = getppid();
      while(!p2_flag) {
        usleep(1000);
      }
      update_file(fd);
      close(fd); 
      p2_flag=0;
      kill(father, SIGUSR2);
      _exit(0);
    }
  }

  for (int j = 0; j < N; j++) {
    while(!p1_flag){
      usleep(1000);
    }
    p1_flag=0;
    kill(sons[j], SIGUSR1);
  }

  while(!p1_flag){
    usleep(1000);
  }
 
  lseek(fd, SEEK_SET, 0);
  read(fd, &r, sizeof(r));
  printf("%d\n", r);

  close(fd);

  return 0;
}

