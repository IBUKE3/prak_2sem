#include <stdio.h>
#include <string.h>

enum {MAXLEN = 255 + 2};


int main(int argc, char* argv[]) {
  if (argc <= 1) return 1;

  char l[MAXLEN];

  FILE* f = fopen(argv[1], "r+");
  FILE* tmf = tmpfile();
  while (fgets(l, sizeof(l), f)) {
    if (strstr(l, argv[2])) {
      fputs(l, tmf);
    }
  }

  fseek(tmf, 0, SEEK_SET);
  fclose(f);
  f = fopen(argv[1], "w"); // clearing the file

  while (fgets(l, sizeof(l), tmf)) {
    fputs(l, f);
  }

  fclose(f);
  fclose(tmf);

  return 0;
}
