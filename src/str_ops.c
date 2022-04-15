#include <ctype.h>

#include "../include/str_ops.h"

//USE LOWER CASE DUMBASS
int lexi_compare(void *ptr1, void *ptr2) {
  char *word1 = ptr1;
  char *word2 = ptr2;

  if(*word1 == 0 && *word2 != 0) { //Left is shorter, smaller
    return -1;
  }
  else if(*word1 != 0 && *word2 == 0) { //Right is shorter, smaller
    return 1;
  }
  else if(*word1 < *word2) { //left is "smaller" word
    return -1;
  }
  else if(*word1 > *word2) { //Right is "smaller" word
    return 1;
  }
  else if(*word1 == 0 && *word2 == 0) { //Same word, order irrelevant
    return 0;
  }
  else if(*word1 == *word2) { //Characters are the same, go deeper
    return lexi_compare((void *) ++word1, (void *) ++word2);
  }
  return 0;
}

void op_str(char *str, int (*operation)(int letter)) {
  if(str == NULL) {
    return;
  }

  if(operation == NULL) {
    return;
  }

  int index = 0;
  while(str[index] != '\0'){
    str[index] = operation(str[index]);
    index++;
  }
}
