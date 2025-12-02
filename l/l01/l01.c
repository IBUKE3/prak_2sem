#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

void sghdlr(int s) {
  static char count = '1';
  char b = '\n';
  if (s == SIGINT) {
    if(write(1, &count, 1)==-1) _exit(1);
    if(write(1, &b, 1)==-1) _exit(1);
    count++;
    if (count=='5') signal(SIGINT, SIG_DFL);
  }
}


int main(void) {
  pid_t p;
  if ((p=fork())==0) {
    signal(SIGINT, sghdlr);
    while(1);
  }
  for (int i = 0; i <=4; i++) {
    usleep(50000);
    kill(p, SIGINT);
    usleep(500);
  }
  while(wait(0) != -1);
  return 0;
}

