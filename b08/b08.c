
int get_bit(unsigned char* m, size_t n) {
  int t = n>>3;
  n&=7;
  unsigned char c = m[t];
  return (c>>n)&1;
}


void set_bit(unsigned char* m, size_t n) {
  int t = n>>3;
  n&=7;
  unsigned char c = 1;
  c<<=n;
  m[t] |= c;
}

void clear_bit(unsigned char* m, size_t n) {
  int t = n>>3;
  n&=7;
  unsigned char c = 1;
  c1 <<= n; // all zeroes, bun one in necessary position
  m[t] &= ~c1; // all ones, but zero in necessary position
}


void toggle_bit(unsigned char* m, size_t n) {
  int t = n>>3;
  n&=7;
  unsigned char c = 1;
  c<<=n;
  m[t] ^= c;
}

