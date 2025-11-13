int mystrcmp(const char * s1, const char * s2){
  int r = 0;
  while ((r == 0)) {
    r = *s1++ - *s2++;
    if ((*s1==0)&&(*s2==0)) return 0;
  }
  return r;
}
