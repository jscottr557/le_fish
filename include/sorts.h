#ifndef SORTS_H
#define SORTS_H

void merge_sort(void *data, long type_size, int left, int right,
                int (*compare)(void *, void *));
#endif
