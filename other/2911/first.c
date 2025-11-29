#include <unistd.h>
#include <signal.h>
#include <stdio.h>


static int x = 1;

void sghdlr(int s) {
  if (s == SIGINT) {
    ++x;
  }
  if (s == SIGQUIT) {
    char* buf = "BYE-BYE!\n";
    write(1, buf, sizeof(buf));
    signal(SIGQUIT, SIG_DFL);
    raise(SIGQUIT);
  }
}


int main(void) {
  signal(SIGINT, sghdlr);
  signal(SIGQUIT, sghdlr); 
  while(1) {
    printf("%d\n", x);
    sleep(1);
  }
}

