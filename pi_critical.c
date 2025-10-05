/*

This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

*/
#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 8
static long num_steps = 10000000000;
double step;
int main() {
  double x, pi, sum = 0.0;
  double start_time, run_time;

  step = 1.0 / (double)num_steps;

  start_time = omp_get_wtime();

  double sums[NUM_THREADS];

  int nthreads;
  omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    double tsum = 0.0;
    int threads = omp_get_num_threads();
    long numBlocks = (num_steps + (threads - 1)) / threads;

    for (long i = numBlocks * tid; i < num_steps && i < numBlocks * (tid + 1);
         i++) {
      double x = (i + 0.5) * step;
      tsum += 4.0 / (1.0 + x * x);
    }
    if (tid == 0) {
      nthreads = threads;
      printf("Number of threads: %d\n", threads);
    }
#pragma omp critical
    sum += tsum;
  }

  pi = step * sum;
  run_time = omp_get_wtime() - start_time;
  printf("\n pi with %ld steps is %lf in %lf seconds\n ", num_steps, pi,
         run_time);
}
