#include <unistd.h>
#include <signal.h>
#include <stdio.h>

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


int main(void) {
  int N;
  setbuf(stdout, 0);

  signal(SIGUSR1, sghdlr);
  signal(SIGUSR2, sghdlr); 

  pid_t son;

  if(!scanf("%d", &N)) return 1;

  if ((son=fork())==0) {
    pid_t father = getppid();
    for (int i = 1; i <= N; i++) {
      while(!p2_flag) {
        usleep(1000);
      }
      printf("%d\n", i);
      p2_flag=0;
      kill(father, SIGUSR2);
    }
    _exit(0);
  }

  p1_flag = 1;
  for (int i = 1; i<= N; i++) {
	  //printf("oki");
    while(!p1_flag){
      usleep(1000);
    }
    printf("%d\n", i);
    p1_flag=0;
    kill(son, SIGUSR1);
  }

  return 0;
}

