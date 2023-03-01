#ifndef MERGE_H
#define MERGE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void print_elts(int64_t *elts, size_t size)
{
  for(size_t i=0; i<size; i++)
    printf("%lld\n", elts[i]);
}

int64_t* merge(int64_t *elts1, int64_t *elts2, size_t size)
{
  size_t lp = size / 2;
  size_t cc = 0;

  int64_t *copy = (int64_t *) malloc(sizeof(int64_t) * size);

  size_t i=0, j=0;

  // merge
  for(; i<lp && j<(size-lp);)
    if(elts1[i] < elts2[j])
      copy[cc++] = elts1[i++];
    else
      copy[cc++] = elts2[j++];

  // copy the remaining items
  if(i<lp)
    while(cc < size && i<lp)
      copy[cc++] = elts1[i++];
  else if(j<(size-lp))
    while(cc < size && j<(size-lp))
      copy[cc++] = elts2[j++];

  // copy back and dealloc temp space
  for(size_t i = 0; i<size; i++)
    elts1[i] = copy[i];

  free(copy);
  return elts1;
}

int64_t *merge_sort(int64_t* elts, size_t size)
{
  int64_t *copy;
  int64_t tmp;

  // base cases
  if(size == 1) {
    copy = elts;
  } else if(size == 2) {
      if(elts[0] > elts[1]) { // swap
        tmp = elts[0];
        elts[0] = elts[1];
        elts[1] = tmp;
      }
      copy = elts;
  } else {
    size_t p = size / 2;
    int64_t *lp = merge_sort(elts, p);
    int64_t *rp = merge_sort(elts+p, size-p);
    copy = merge(lp, rp, size);
  }

  return copy;
}

#endif // MERGE_H
