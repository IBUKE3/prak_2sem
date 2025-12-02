#include <unistd.h>
#include <signal.h>
#include <stdio.h>


void sghdlr(int s) {
  static int flag = 0;
  if (s == SIGINT) {
    if (flag) {
      if(write(1, "Bye-bye!\n", 9)==-1) _exit(1);
      _exit(0);
    }
    if (write(1, "Hi!\n", 4)==-1) _exit(1);
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

