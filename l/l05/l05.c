#include <unistd.h>
#include <signal.h>
#include <stdio.h>


void sghdlr(int s) {
  static int int_counter = 0;
  static int term_counter = 0;
  if (s == SIGINT) {
    int_counter++;
    if (int_counter&1) {
      write(0, "LOMONOSOV\n", 10);
    }
  }
  if (s == SIGTERM) {
    term_counter++;
    if (term_counter==4) {
      write(0, "COOL\n", 5);
      _exit(0);
    }
  }
}


int main(void) {
  signal(SIGINT, sghdlr);
  signal(SIGTERM, sghdlr); 
  while(1) {
    sleep(1);
  }
  return 0;
}

