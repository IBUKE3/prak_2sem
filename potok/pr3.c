#include <stdio.h>
typedef long long ll;

int main(void) {
  int a, b, n;

  if (scanf("%d%d%d", &a, &b, &n) != 3) return 1;

  for (int i = 0; i < n; i++) printf(" ");
  for (int i = a; i < b; i++) {
    printf(" %*d", n, i);
  }
  printf("\n");

  for (int i = a; i < b; i++) {
    printf("%*d", n, i);
    for (int j = a; j < b; j++) {
      printf(" %*lld", n, (ll) i*j);
    }
    printf("\n");
  }

  return 0;
}

