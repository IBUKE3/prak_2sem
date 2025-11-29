#include <unistd.h>
#include <signal.h>
#include <stdio.h>


static int x = 1;

void sghdlr(int s) {
  static int flag = 0;
  if (s == SIGINT) {
    if (flag) {
      write(1, "DIE\n", 4);
      _exit(0);
    }
    write(1, "Hi!\n", 4);
    flag = 1;
    alarm(1);
  }
  if (s == SIGALRM) {
    flag = 0;
  }
}


int main(void) {
  signal(SIGINT, sghdlr);
  signal(SIGALRM, sghdlr); 
  while(1) {
    sleep(1);
  }
}

