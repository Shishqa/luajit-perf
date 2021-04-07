#include <unistd.h>
#include <stdio.h>

#include "benchmark/benchmark.h"

int main() {
  printf("%d\n", getpid());
  run_benchmark(NULL, NULL);
  return 0;
}
