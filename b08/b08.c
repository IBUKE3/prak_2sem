
int get_bit(unsigned char* m, size_t n) {
  int t = n/8;
  n%=8;
  unsigned char c = m[t];
  return (c>>n)&1;
}


void set_bit(unsigned char* m, size_t n) {
  int t = n/8;
  n%=8;
  unsigned char c = 1;
  c<<=n;
  m[t] |= c;
}

void clear_bit(unsigned char* m, size_t n) {
  int t = n/8;
  n%=8;
  unsigned char c = 0xFF;
  unsigned char c1 = 1;
  c1 <<= n;
  c ^= c1; // all ones, but zero in right position
  m[t] &= c;
}


void toggle_bit(unsigned char* m, size_t n) {
  int t = n/8;
  n%=8;
  unsigned char c = 1;
  c<<=n;
  m[t] ^= c;
}

