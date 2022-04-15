#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/sorts.h"

#define DEBUG

void merge(void *data, long type_size, int left, int middle, int right,
           int (*compare)(void *, void *)) {

  //Placeholder for user-defined type so we can do arr manip
  typedef char type_t[type_size];

  //Calculate sub-array length
  int sub_arr_length = ((right - left) / 2) + 1;
  int left_elements = middle - left + 1;
  int right_elements = right - middle;

  //Allocate memory for duplicate arrays
  type_t *left_array = malloc(type_size * (sub_arr_length));
  type_t *right_array = malloc(type_size * (sub_arr_length));

  //Copy data to duplicate arrays
  type_t *data_ptr = data;
  for(int i = 0; i < sub_arr_length; i++) {
    memcpy(left_array + i, data_ptr + left + i, type_size);
    memcpy(right_array + i, data_ptr + middle + 1 + i, type_size);
  }

  //Tracks position in copied array
  int left_arr_pos = 0;
  int right_arr_pos = 0;

  //Merge back onto original array
  for(int i = 0; i < right - left+1; i++) {
    if(left_arr_pos == left_elements) {
      //If out of left array members, write right to main array
      memcpy(data_ptr + left + i, right_array + right_arr_pos, type_size);
      right_arr_pos++;
    }
    else if(right_arr_pos == right_elements) {
      //If out of right array members, write left to main array
      memcpy(data_ptr + left + i, left_array + left_arr_pos, type_size);
      left_arr_pos++;
    }
    else if(compare(left_array[left_arr_pos], right_array[right_arr_pos])
                    <= 0) {
      //Left is "smaller", write over next pos in main array, bump left pos
      memcpy(data_ptr + left + i, left_array + left_arr_pos, type_size);
      left_arr_pos++;
    }
    else {
      //Right is "smaller", write over next pos in main array and bump right pos
      memcpy(data_ptr + left + i, right_array + right_arr_pos, type_size);
      right_arr_pos++;
    }
  }

  free(left_array);
  free(right_array);

  return;
}


void merge_sort(void *data, long type_size, int left, int right,
                int (*compare)(void *, void *)) {
  if(right - left == 0) {
    return;
  }

  int middle = (right + left) / 2;

  merge_sort(data, type_size, left, middle, compare);
  merge_sort(data, type_size, (middle+1), right, compare);

  merge(data, type_size, left, middle, right, compare);
}
