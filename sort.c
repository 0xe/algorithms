#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#include "merge.h"
#include "quick.h"

void populate_elts(int64_t *elts, size_t size)
{
  for(size_t i=0; i<size; i++)
    elts[i] = rand() % INT64_MAX;
}

int int64_cmp(const void *a, const void *b)
{
  return (*(int64_t *)a) - (*(int64_t *)b);
}

int main(int argc, const char *argv[])
{
  if(argc != 2)
    return -1;

  clock_t start, end;
  double cpu_time;

  size_t size = atoi(argv[1]);
  srand(time(0));

  int64_t *elts = (int64_t *) malloc(sizeof(int64_t) * size);

  // try system qsort
  {
    populate_elts(elts, size);

    start = clock();
    qsort(elts, size, sizeof(int64_t), int64_cmp);

    end = clock();
    cpu_time = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("system qsort %fms\n", cpu_time*1000);
  }

  // try our merge sort
  {
    populate_elts(elts, size);

    start = clock();
    elts = merge_sort(elts, size);

    end = clock();
    cpu_time = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("merge sort %fms\n", cpu_time*1000);
  }

  // try our qsort
  {
    populate_elts(elts, size);

    start = clock();
    quick_sort(elts, size);

    end = clock();
    cpu_time = ((double) (end - start) / CLOCKS_PER_SEC);
    printf("quick sort %fms\n", cpu_time*1000);
  }

  free(elts);
}
