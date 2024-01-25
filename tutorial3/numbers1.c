#include <stdio.h>

int main() {
  char a = 187;
  char b = 76;
  char c = (unsigned char) 267;
  short d = a + b;
  
  printf("a + b = %d\n", a + b);
  printf("c = %d\n", c);
  printf("d = %d\n", d);
}
