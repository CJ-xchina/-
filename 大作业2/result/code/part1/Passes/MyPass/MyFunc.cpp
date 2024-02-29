#include <stdio.h>

extern "C" __attribute__((visibility("default"))) void printHello()
{
  printf("instrumentation hello\n");
}
