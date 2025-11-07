#include <stdio.h>
#include <stdlib.h>

int get_bit(unsigned char* m, size_t n) {
  int t = n>>3;
  n&=7;
  unsigned char c = m[t];
  return (c>>n)&1;
}


void toggle_bit(unsigned char* m, size_t n) {
  int t = n>>3;
  n&=7;
  unsigned char c = 1;
  c<<=n;
  m[t] ^= c;
}


size_t max_seq1(unsigned char * m, size_t size) {
  int res = 0;
  int cur = 0;
  for (int i = 0; i < size; i++) {
    if (get_bit(m, i)){
	    cur++;
    }
    else { 
      res = (cur>res)?cur:res;
      cur = 0;
    }
  }
  res = (cur>res)?cur:res;
  return res;
}


int main(int argc, char* argv[]){
  FILE* f = fopen(argv[1], "r+");
  fseek(f, 0, SEEK_END);
  long file_size = ftell(f);

  unsigned char* m = calloc(sizeof(unsigned char), file_size);

  fseek(f, 0, SEEK_SET);
  if(fread(m, sizeof(unsigned char), file_size, f) != file_size) return 1;

  int numbits = file_size*8;

  int maxones = max_seq1(m, numbits);

  int left = -1;

  for (int i = 0; i < numbits; i++){
    if (get_bit(m, i)) { 
      if (left==-1) {
	left = i; // putting left border
      } 
      if (i-left+1==maxones) {
        for (int j = left; j <= i; j++) {
          toggle_bit(m, j);
        }
      }
    } else {
      left = -1;
    }
  }

  fseek(f, 0, SEEK_SET); // no need to erase current elements, better overwrite
  

  fwrite(m, sizeof(unsigned char), file_size, f);

  free(m);
  fclose(f);

  return 0;
}

