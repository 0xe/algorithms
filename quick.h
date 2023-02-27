#include <math.h>

void swap(int64_t *elts, size_t l, size_t r)
{
  int64_t temp = elts[l];
  elts[l] = elts[r];
  elts[r] = temp;
}

// this is really one of CS' greatest hits!
void quick_sort(int64_t *elts, size_t size)
{
  if(size == 0) return;

  size_t pivot = rand() % size; size_t last = 0;
  swap(elts, 0, pivot);

  for(size_t i = 1; i < size; i++)
    if(elts[i] < elts[0])
      swap(elts, i, ++last);

  swap(elts, 0, last);
  quick_sort(elts, last);
  quick_sort(elts+last+1, size-last-1);
}
