#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void){
  setbuf(stdin, 0);
  int s, c;
  s = fgetc(stdin);
  while ((c = fgetc(stdin))!= -1) {
    int r = fork(); 
    if (r==0) {
      if (c == s) {putc(c, stdout); putc(c, stdout);};
      exit(0);
    } else if (r==-1) {
      wait(NULL);
      if (fork()==0) {	     
	if (c==s) {putc(c, stdout); putc(c, stdout);};
        exit(0);
      }
    }
  }

  
  while (wait(NULL)!=-1) continue;
  putc('\n', stdout);

  return 0;
}

