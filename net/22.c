#include <stdio.h>
#include <stdlib.h>

int IsHELLO(const char *src) {
  if (src == NULL) {
    return 0;
  }
  int i = 0;
  char hello[10] = "HELLO";
  while (src++) {
    if (src[i] != hello[i]) {
      return 0;
    }
  }

  return 1;
}
int ISWorld(const char *src) {
  return 0;
}

int main() {
  int a = IsHELLO("HELLO");
  printf("%d\n", a);
  return 0;
}